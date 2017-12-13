#include "stdafx.h"
#include "Rasterizer.h"

Rasterizer::Rasterizer(Buffer* buff) : buffer(buff)
{ }

Rasterizer::~Rasterizer()
{ }

void Rasterizer::Triangle(VertexProcessor& vp, const float3& v1, const float3& v2, const float3& v3, const float3& c1, const float3& c2, const float3& c3, const float3& n1, const float3& n2, const float3& n3, Material* mat)
{
    float3 tc1 = vp.lt({ v1, n1, c1 }, *mat);
    float3 tc2 = vp.lt({ v2, n2, c2 }, *mat);
    float3 tc3 = vp.lt({ v3, n3, c3 }, *mat);

    int x1 = (v1.x + 1) * buffer->Width() *.5f,
        x2 = (v2.x + 1) * buffer->Width() *.5f,
        x3 = (v3.x + 1) * buffer->Width() *.5f;
    int y1 = (v1.y + 1) * buffer->Height() *.5f,
        y2 = (v2.y + 1) * buffer->Height() *.5f,
        y3 = (v3.y + 1) * buffer->Height() *.5f;

    //rectangle of the triangle calculations
    int minx = std::max(Min(x1, x2, x3), 0),
        maxx = std::min(Max(x1, x2, x3), buffer->Width() - 1),
        miny = std::max(Min(y1, y2, y3), 0),
        maxy = std::min(Max(y1, y2, y3), buffer->Height() - 1);
    //constants
    int
        dx12 = x1 - x2,
        dx23 = x2 - x3,
        dx31 = x3 - x1,
        dy12 = y1 - y2,
        dy23 = y2 - y3,
        dy31 = y3 - y1;
    float db1 = 1.f / (-dy23 * dx31 + dx23 * dy31);
    float db2 = 1.f / (dy31 * dx23 - dx31 * dy23);

    //topleft calculations
    bool tl1 = false, tl2 = false, tl3 = false;

    if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) { tl1 = true; }
    if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) { tl2 = true; }
    if (dy31 < 0 || (dy31 == 0 && dx31 > 0)) { tl3 = true; }

    for (int y = miny; y < maxy; ++y)
    {
        for (int x = minx; x < maxx; ++x)
        {
            if (((tl1 && dx12*(y - y1) - dy12*(x - x1) >= 0) || (!tl1 && dx12*(y - y1) - dy12*(x - x1) > 0)) &&
                ((tl2 && dx23*(y - y2) - dy23*(x - x2) >= 0) || (!tl2 && dx23*(y - y2) - dy23*(x - x2) > 0)) &&
                ((tl3 && dx31*(y - y3) - dy31*(x - x3) >= 0) || (!tl3 && dx31*(y - y3) - dy31*(x - x3) > 0)))
            {
                //which position on buffer
                int n = y*buffer->Width() + x;
                //baricentric
                float
                    d1 = (dy23 * (x - x3) - dx23 * (y - y3)) * db1,
                    d2 = (dy31 * (x - x3) - dx31 * (y - y3)) * db2,
                    d3 = 1 - d1 - d2;
                //checking depth
                float depth = (d1 * v1.z + d2 * v2.z + d3 * v3.z);

                if (depth >= 0 && depth < buffer->m_Depth[n])
                {
                    //color calculations
                    float3 color = vp.lt({
                        d1 * v1 + d2 * v2 + d3 * v3,
                        d1 * n1 + d2 * n2 + d3 * n3,
                        d1 * tc1 + d2 * tc2 + d3 * tc3
                    }, *mat);

                    buffer->m_Color[n] = ColorToUint(color);
                    buffer->m_Depth[n] = depth;
                }
            }
        }
    }
}