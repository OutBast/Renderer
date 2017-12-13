#include "stdafx.h"
#include "Light.h"
#include "Data.h"

Light::Light(VertexProcessor* vp, const float3& position, const float3& color, const float3& ambient) :
    position(position), color(color), ambient(ambient)
{
    Data::Instance().lights.push_back(this);
    if (vp)
    {
        this->position = //mul(vp->world2view, this->position);
            vp->tr(this->position);
    }
}

Light::~Light()
{
}