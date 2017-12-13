#pragma once
#include "Buffer.h"
#include "Material.h"
#include "VertexProcessor.h"

class Rasterizer
{
public:
    Rasterizer(Buffer* buff);
    ~Rasterizer();

    void Triangle(
        VertexProcessor& vp,
        const float3& v1, const float3& v2, const float3& v3,
        const float3& c1, const float3& c2, const float3& c3,
        const float3& n1, const float3& n2, const float3& n3,
        Material* mat
    );

private:
    Buffer* buffer;
};

