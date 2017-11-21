#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle() :
    vertices({ float3::zero, float3::zero, float3::zero }),
    barycentric({ 0.0f, 0.0f, 0.0f }),
    normal(float3::up)
{
    CalculateSurfaceArea();
    CalculateMaxDistances();
}


Triangle::Triangle(const float3 &v1, const float3 &v2, const float3 &v3, const float3 &normal, Material &material) :
    Primitive((v1 + v2 + v3) * 0.333f, &material),
    vertices({ v1, v2, v3 }),
    barycentric({ 0.0f, 0.0f, 0.0f }),
    normal(normal)
{
    CalculateSurfaceArea();
    CalculateMaxDistances();
}

Triangle::Triangle(const Triangle &triangle) :
    Primitive((triangle.Vertices()[0] + triangle.Vertices()[1] + triangle.Vertices()[2]) * 0.333f, triangle.material),
    vertices({ triangle.Vertices()[0], triangle.Vertices()[1], triangle.Vertices()[2] }),
    barycentric({ triangle.barycentric[0], triangle.barycentric[1], triangle.barycentric[2] }),
    normal(triangle.Normal()),
    verticesUVW({ triangle.VerticesUVW()[0], triangle.VerticesUVW()[1], triangle.VerticesUVW()[2] })
{
    CalculateSurfaceArea();
    CalculateMaxDistances();
}

Triangle::Triangle(const float3 &v1, const float3 &v2, const float3 &v3, const float3 &normal, Material &material, const float3 &v1T, const float3 &v2T, const float3 &v3T) :
    Primitive((v1 + v2 + v3) * 0.333f, &material),
    vertices({ v1, v2, v3 }),
    barycentric({ 0.0f, 0.0f, 0.0f }),
    normal(normal),
    verticesUVW({ v1T, v2T, v3T })
{
    CalculateSurfaceArea();
    CalculateMaxDistances();
}

Triangle::Triangle(const float3 &v1, const float3 &v2, const float3 &v3) :
    Primitive((v1 + v2 + v3) * 0.333f, nullptr),
    vertices({ v1, v2, v3 }),
    barycentric({ 0.0f, 0.0f, 0.0f }),
    normal(normal)
{
    CalculateSurfaceArea();
    CalculateMaxDistances();
}

Triangle::~Triangle()
{ }

void Triangle::CalculateSurfaceArea()
{
    float3 firstVec = vertices[0] - vertices[1];
    float3 secondVec = vertices[2] - vertices[1];

    surfaceArea = 0.5f * firstVec.Magnitude() * secondVec.Magnitude() * sin(DegreesToRadians(float3::Angle(firstVec, secondVec)));
}

void Triangle::CheckValueForInf(float& value)
{
    if (isinf(value))
    {
        value = 0.0F;
    }
}

void Triangle::CalculateMaxDistances()
{
    maxXDistance = fmaxf(fabsf(vertices[0].X() - center.X()), fmaxf(fabsf(vertices[1].X() - center.X()), fabsf(vertices[2].X() - center.X())));
    maxYDistance = fmaxf(fabsf(vertices[0].Y() - center.Y()), fmaxf(fabsf(vertices[1].Y() - center.Y()), fabsf(vertices[2].Y() - center.Y())));
    maxZDistance = fmaxf(fabsf(vertices[0].Z() - center.Z()), fmaxf(fabsf(vertices[1].Z() - center.Z()), fabsf(vertices[2].Z() - center.Z())));
    maxOfMaxDistances = max(maxXDistance, max(maxYDistance, maxZDistance));
}

Primitive* Triangle::Clone() const
{
    return new Triangle(*this);
}

std::ostream &operator<<(std::ostream &os, const Triangle &value)
{
    os << "Triagle - v1: " << value.Vertices()[0] << ", v2: " << value.Vertices()[1] << ", v3: " << value.Vertices()[2] << endl;
    os << "Normal: " << value.Normal() << endl;
    os << "Surface Area: " << value.SurfaceArea() << endl;

    return os;
}