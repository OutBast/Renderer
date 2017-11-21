#pragma once

#include "float3.h"
#include "Material.h"

class Ray;

class Primitive
{
public:
    Primitive();
    Primitive(const float3 center);
    Primitive(Material *material);
    Primitive(const float3 center, Material *material);
    ~Primitive();

    virtual Primitive* Clone() const = 0;
    void CalculateDistanceToCamera(float3& camPos);

    friend std::ostream &operator<<(std::ostream &os, const Primitive &value);

    float3 Center() const { return center; }
    void Center(float3 val) { center = val; }
    float DistanceToCamera() const { return distanceToCamera; }
    void DistanceToCamera(float val) { distanceToCamera = val; }

    Material *material;
protected:
    float3 center;
    float distanceToCamera;
};
