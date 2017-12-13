#pragma once
#include "Vertex.h"
#include "Material.h"
class VertexProcessor
{
public:
    VertexProcessor();
    ~VertexProcessor();

    float3 tr(const float3& position);
    Vertex tr(const Vertex& v);
    //Vertex lt(const Vertex& f);
    float3 lt(const Vertex& v, const Material& mat);

    void SetPerspective(float fov, float aspect, float near, float z_far);
    void SetLookAt(const float3& eye, const float3& target, const float3& up);
    void SetIdentity();
    void Translate(const float3& v);
    void Rotate(const float3& axis, float angle);
    void Scale(const float3& scale);


    void calculateFinalMatrixAkaTransform();

    float4x4 obj2world;
    float4x4 world2view;
    float4x4 view2proj;

    float4x4 obj2view;
    float4x4 obj2proj;
};

