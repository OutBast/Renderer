#include "stdafx.h"
#include "Rasterizer.h"

Rasterizer::Rasterizer(Buffer* buff) : buffer(buff)
{ }

Rasterizer::~Rasterizer()
{ }

void Rasterizer::Triangle(const float3& v1, const float3& v2, const float3& v3,
                          const float3& c1 = float3(1.0f, 0.0f, 0.0f), const float3& c2 = float3(0.0f, 1.0f, 0.0f), const float3& c3 = float3(0.0f, 0.0f, 1.0f))
{
    float y1 = TransformNDCSpaceToScreenSpace(v1.Y(), buffer->Height());
    float y2 = TransformNDCSpaceToScreenSpace(v2.Y(), buffer->Height());
    float y3 = TransformNDCSpaceToScreenSpace(v3.Y(), buffer->Height());

    float x1 = TransformNDCSpaceToScreenSpace(v1.X(), buffer->Width());
    float x2 = TransformNDCSpaceToScreenSpace(v2.X(), buffer->Width());
    float x3 = TransformNDCSpaceToScreenSpace(v3.X(), buffer->Width());

    float dx12 = x1 - x2;
    float dx23 = x2 - x3;
    float dx31 = x3 - x1;
    float dy12 = y1 - y2;
    float dy23 = y2 - y3;
    float dy31 = y3 - y1;

    float delta1, delta2, delta3;

    // Bounding rectangle
    buffer->MinX((int)min({ x1, x2, x3 }));
    buffer->MaxX((int)max({ x1, x2, x3 }));
    buffer->MinY((int)min({ y1, y2, y3 }));
    buffer->MaxY((int)max({ y1, y2, y3 }));

    buffer->MinX((int)max(buffer->MinX(), 0));
    buffer->MaxX((int)min(buffer->MaxX(), buffer->Width() - 1));
    buffer->MinY((int)max(buffer->MinY(), 0));
    buffer->MaxY((int)min(buffer->MaxY(), buffer->Height() - 1));

    bool tl1 = false, tl2 = false, tl3 = false;

    if (dy12 < 0.0f || (dy12 == 0.0f && dx12 > 0.0f))
    {
        tl1 = true;
    }
    if (dy23 < 0.0f || (dy23 == 0.0f && dx23 > 0.0f))
    {
        tl2 = true;
    }
    if (dy31 < 0.0f || (dy31 == 0.0f && dx31 > 0.0f))
    {
        tl3 = true;
    }
    // Scan through bounding rectangle
    for (int y = buffer->MinY(); y < buffer->MaxY(); ++y)
    {
        for (int x = buffer->MinX(); x < buffer->MaxX(); ++x)
        {
            // When all half-space functions positive, pixel is in triangle
            if ((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0.0f && 
                (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0.0f &&
                (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0.0f)
            {
                delta1 = ((dy23 * (x - x3)) + (-dx23 * (y - y3))) / ((dy23 * -dx31) + (-dx23 * -dy31));
                delta2 = ((dy31 * (x - x3)) + (-dx31 * (y - y3))) / ((dy31 * dx23) + (-dx31 * dy23));
                delta3 = 1.0f - delta1 - delta2;

                buffer->m_Color[x + y * buffer->Width()] = ColorToUint(delta1 * c1 + delta2 * c2 + delta3 * c3);
            }
            //top left filling
            if (tl1 || tl2 || tl3)
            {
                if ((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) >= 0.0f &&
                    (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) >= 0.0f &&
                    (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) >= 0.0f)
                {
                    delta1 = ((dy23 * (x - x3)) + (-dx23 * (y - y3))) / ((dy23 * -dx31) + (-dx23 * -dy31));
                    delta2 = ((dy31 * (x - x3)) + (-dx31 * (y - y3))) / ((dy31 * dx23) + (-dx31 * dy23));
                    delta3 = 1.0f - delta1 - delta2;

                    buffer->m_Color[x + y * buffer->Width()] = ColorToUint(delta1 * c1 + delta2 * c2 + delta3 * c3);
                }
            }
        }
    }

}

float Rasterizer::TransformNDCSpaceToScreenSpace(float v, int offset)
{
    return (v + 1.0f) * offset * 0.5f;
}
