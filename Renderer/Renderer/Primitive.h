#pragma once

#include "float3.h"
#include "Material.h"

class Ray;

class Primitive
{
public:
    Primitive();
    Primitive(const float3 center, const bool &useVerticesUVW);
    Primitive(Material *material, const bool &useVerticesUVW);
    Primitive(const float3 center, Material *material, const bool &useVerticesUVW);
    ~Primitive();

    virtual Primitive* Clone() const = 0;
    virtual bool Intersect(Ray &ray, bool photon = false) = 0;
    virtual void IntersectionOutput(const Ray &ray) = 0;
    virtual float3 LocalIntersectionPoint(const float3 &worldIntersectionPoint, const float& scale) = 0;
    virtual float3 GetUVW(const float3& globalIntersectionPoint) = 0;
    void CalculateDistanceToCamera(float3& camPos);

    friend std::ostream &operator<<(std::ostream &os, const Primitive &value);

    float3 Center() const { return center; }
    void Center(float3 val) { center = val; }
    float DistanceToCamera() const { return distanceToCamera; }
    void DistanceToCamera(float val) { distanceToCamera = val; }
    bool UseVerticesUVW() const { return useVerticesUVW; }
    void UseVerticesUVW(bool val) { useVerticesUVW = val; }


    Material *material;
protected:
    float3 center;
    float distanceToCamera;
    bool useVerticesUVW;

    virtual float CalculateLocalIntersectionPoint(const float& point, const float& scale);
};
