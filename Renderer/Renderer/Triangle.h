#pragma once

#include "Primitive.h"

class Triangle :
    public Primitive
{
public:
    Triangle();
    Triangle(const Triangle &triangle);
    Triangle(const float3 &v1, const float3 &v2, const float3 &v3, const float3 &normal, Material &material);
    Triangle(const float3 &v1, const float3 &v2, const float3 &v3, const float3 &normal, Material &material, const float3 &v1T, const float3 &v2T, const float3 &v3T);
    ~Triangle();

    virtual bool Intersect(Ray &ray, bool photon = false) override;
    virtual void IntersectionOutput(const Ray &ray) override;

    friend std::ostream &operator<<(std::ostream &os, const Triangle &value);

    std::array<float3, 3> Vertices() const { return vertices; }
    void Vertices(std::array<float3, 3> val) { vertices = val; }
    float SurfaceArea() const { return surfaceArea; }
    void SurfaceArea(float val) { surfaceArea = val; }
    float3 Normal() const { return normal; }
    void Normal(float3 val) { normal = val; }

    virtual Primitive* Clone() const override;


    virtual float3 LocalIntersectionPoint(const float3 &worldIntersectionPoint, const float& scale) override;


    virtual float3 GetUVW(const float3& globalIntersectionPoint) override;

    std::array<float3, 3> VerticesUVW() const { return verticesUVW; }
    void VerticesUVW(std::array<float3, 3> val) { verticesUVW = val; }
private:
    float3 normal;
    std::array<float3, 3> vertices;
    std::array<float3, 3> verticesUVW;
    std::array<float, 3> barycentric;
    float surfaceArea;

    float maxXDistance;
    float maxYDistance;
    float maxZDistance;
    float maxOfMaxDistances;

    void CalculateSurfaceArea();
    void CheckValueForInf(float& value);
    void CalculateMaxDistances();
};

