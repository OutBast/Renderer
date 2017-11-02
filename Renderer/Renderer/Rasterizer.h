#pragma once
#include "Buffer.h"

class Rasterizer
{
public:
    Rasterizer(Buffer* buff);
    ~Rasterizer();

    void Triangle(const float3& v1, const float3& v2, const float3& v3,
                  const float3& c1, const float3& c2, const float3& c3);

private:
    float TransformNDCSpaceToScreenSpace(float v, int offset);

    Buffer* buffer;
};

