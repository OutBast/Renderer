#include "stdafx.h"
#include "VertexProcessor.h"


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

float3 VertexProcessor::lt()
{
    return float3::zero;
}

void VertexProcessor::SetPerspective(float fov, float aspect, float z_near, float z_far)
{
    fov *= M_PI / 360.0f;
    float f = cos(fov) / sin(fov);
    view2proj[0] = float4(f / aspect, 0.0f, 0.0f, 0.0f);
    view2proj[1] = float4(0.0f, f, 0.0f, 0.0f);
    view2proj[2] = float4(0.0f, 0.0f, (z_far + z_near) / (z_near - z_far), -1.0f);
    view2proj[3] = float4(0.0f, 0.0f, 2.0f * z_far * z_near / (z_near - z_far), 0.0f);
}

void VertexProcessor::SetLookAt(const float3& eye, const float3& target, const float3& up)
{
    float3 f = target - eye;
    f.Normalized();
    float3 s = float3::Cross(f, up);
    float3 u = float3::Cross(s, f);
    world2view[0] = float4(s[0], u[0], -f[0], 0);
    world2view[1] = float4(s[1], u[1], -f[1], 0);
    world2view[2] = float4(s[2], u[2], -f[2], 0);
    world2view[3] = float4(-eye);
}

void VertexProcessor::SetIdentity()
{
    obj2world = world2view = view2proj = float4x4::IDENTITY;
}

void VertexProcessor::Translate(const float3& v)
{
    float4x4 mtx44 = obj2world;
    obj2world = mtx44.Translate(v);
}

void VertexProcessor::Rotate(const float3& axis, float angle)
{
    float4x4 mtx44 = obj2world;
    obj2world = mtx44.Rotation(axis, angle);
}

void VertexProcessor::Scale(const float3& scale)
{
    float4x4 mtx44 = obj2world;
    obj2world *= mtx44.Scale(scale);
}

void VertexProcessor::calculateFinalMatrixAkaTransform()
{
    obj2view = world2view * obj2world;
    obj2proj = view2proj * obj2view;
}
