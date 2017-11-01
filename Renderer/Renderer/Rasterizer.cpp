#include "stdafx.h"
#include "Rasterizer.h"

Rasterizer::Rasterizer(Buffer* buff) : buffer(buff)
{ }

Rasterizer::~Rasterizer()
{ }

void Rasterizer::Triangle(const float3& v1, const float3& v2, const float3& v3,
					      uint c1, uint c2, uint c3)
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

	// Scan through bounding rectangle
	for (int y = buffer->MinY(); y < buffer->MaxY(); ++y)
	{
		for (int x = buffer->MinX(); x < buffer->MaxX(); ++x)
		{
			buffer->m_Color[x + y * buffer->Width()] = 0x00ffffff; // White
			// When all half-space functions positive, pixel is in triangle
			if ((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0 && 
				(x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0 &&
				(x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0)
			{
				delta1 = ((dy23 * (x - x3)) + (-dx23 * (y - y3))) / ((dy23 * -dx31) + (-dx23 * -dy31));
				delta2 = ((dy31 * (x - x3)) + (-dx31 * (y - y3))) / ((dy31 * dx23) + (-dx31 * dy23));
				delta3 = 1.0f - delta1 - delta2;

				buffer->m_Color[x + y * buffer->Width()] = delta1 * c1 + delta2 * c2 + delta3 * c3;
			}
		}
	}

}

float Rasterizer::TransformNDCSpaceToScreenSpace(float v, int offset)
{
	return (v + 1.0f) * offset * 0.5f;
}