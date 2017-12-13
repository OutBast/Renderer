#include "stdafx.h"
#include "DirectionalLight.h"

#include <algorithm>

DirectionalLight::DirectionalLight(VertexProcessor* vp, const float3 & dir, const float3 & color, const float3 & ambient) :
    Light( vp, { 0,0,0 }, color, ambient), dir(dir)
{
    if (vp) {
        //this->dir = vp->tr(dir);
        this->dir = (float3)mul(mul(vp->world2view, vp->view2proj), { this->dir,0 });
        this->dir.Normalize();//
    }
}

DirectionalLight::~DirectionalLight()
{
}

const float3 & DirectionalLight::Dir() const
{
    return dir;
}

//float3 DirectionalLight::getLightInPoint(const float3 & normal, const float3 & pos, const Material& mat)
//{
//    float3 res{};
//    float3 spec{};
//    float intensity = std::max(float3::Dot(normal, -1.f * dir), 0.f);
//
//    if (intensity > 0.f)
//    {
//        float3 eye = (-1.f * pos).Normalized();
//        float3 h = (eye - dir).Normalized();
//
//        float intSpec = std::max(float3::Dot(h, normal), 0.f);
//        spec = mat.ColorSpecular() * pow(intSpec, mat.Ns());
//    }
//    res = intensity * color * mat.ColorDiffuse() + spec;
//
//    ClampColor(res);
//    //res.normalizeColor();
//    std::cout << "i: " << intensity << ", s: " << spec << "\n";
//    return res;
//}