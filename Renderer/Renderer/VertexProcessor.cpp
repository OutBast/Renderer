#include "stdafx.h"
#include "VertexProcessor.h"
#include "Data.h"


VertexProcessor::VertexProcessor() : 
    obj2world(float4x4::IDENTITY),
    world2view(float4x4::IDENTITY),
    view2proj(float4x4::IDENTITY),
    obj2view(float4x4::IDENTITY),
    obj2proj(float4x4::IDENTITY)
{
}


VertexProcessor::~VertexProcessor()
{
}

float3 VertexProcessor::tr(const float3& position)
{
    float4 pos = float4(position);
    float4 result = obj2proj * pos;
    return float3(result.x, result.y, result.z) / result.w;
}

Vertex VertexProcessor::tr(const Vertex& v)
{
    Vertex res{ v };

    res.position = tr(v.position);

    return res;
}

float3 VertexProcessor::lt(const Vertex & v, const Material& mat)
{
    float3 col{};
    float3 n{ v.normal };
    float3 tex{ 1,1,1 };

    n.Normalize();

    for (auto * light : Data::Instance().getLights())
    {
        float3 res{};
        float3 spec{};
        float zmienna = float3::Dot(n, light->Dir());
        float intensity = std::max(zmienna, 0.f);

        if (intensity > 0.f)
        {
            float3 eye = v.position.Normalized();
            float3 h = (eye - light->Dir()).Normalized();

            float intSpec = std::max(float3::Dot(h, n), 0.f);
            spec = mat.ColorSpecular() * pow(intSpec, mat.Ns());
            spec *= light->Specular();
        }
        float3 diff = tex * (float3)mat.ColorDiffuse();

        res = intensity * light->Color() * diff + spec;

        ClampColor(res);

        col += res;
    }

    col += Data::Instance().getAmbientLight() * (float3)mat.ColorAmbient() * tex;

    ClampColor(col);

    return col;
}

void VertexProcessor::SetPerspective(float fov, float aspect, float z_near, float z_far)
{
    view2proj = float4x4::createPerspective(fov, aspect, z_near, z_far);
}

void VertexProcessor::SetLookAt(const float3& eye, const float3& target, const float3& up)
{
    world2view = float4x4::createLookAt(eye, target, up);
}

void VertexProcessor::SetIdentity()
{
    obj2world = world2view = view2proj = float4x4::IDENTITY;
}

void VertexProcessor::Translate(const float3& v)
{
    obj2world = float4x4::createTranslation(v) * obj2world;
}

void VertexProcessor::Rotate(const float3& axis, float angle)
{
    obj2world = float4x4::createRotation(DegreesToRadians(angle), axis) * obj2world;
}

void VertexProcessor::Scale(const float3& scale)
{
    obj2world = float4x4::createScale(scale) * obj2world;
}

void VertexProcessor::calculateFinalMatrixAkaTransform()
{
    obj2view = world2view * obj2world;
    obj2proj = view2proj * obj2view;
}
