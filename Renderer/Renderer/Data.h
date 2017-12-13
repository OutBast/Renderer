#pragma once
#include "Light.h"

class Data
{
public:
    Data() {}
    ~Data();
    Data(const Data&) = delete;
    Data & operator=(const Data&) = delete;

    static Data& Instance();

    const std::vector<Light*> & getLights() const { return lights; }
    float3& AmbientLight() { return ambientLight; }
    const float3& getAmbientLight() const { return ambientLight; }

    std::vector<Light*> lights;

    float3 ambientLight;
};

