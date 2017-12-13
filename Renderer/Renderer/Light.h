#pragma once
#include "VertexProcessor.h"

class Light
{
public:
    Light(VertexProcessor* vp, const float3& position, const float3& color, const float3& ambient);
    Light() : Light(nullptr, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }) {};
    ~Light();

    float3& Position() { return position; }
    float3& Color() { return color; }
    float3& Specular() { return specular; }
    virtual const float3& Dir() const = 0;
protected:
    float3 position;
    float3 color;
    float3 ambient;
    float3 specular;
};

