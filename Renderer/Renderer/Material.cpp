#include "stdafx.h"
#include "Material.h"

#define NFACTOR 2.24f
#define POWER_FACTOR 0.5f


Material::Material() :
    //colorAmbient(float4::black),
    typeOfMaterial(MaterialType::MATTE),
    m_n(NFACTOR),
    diffuseReflectionCoefficient(float4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR)),
    specularReflectionCoefficient(float4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR))
{ }


Material::Material(const float4 &colorAmbient, MaterialType typeOfMaterial, float n) :
    colorAmbient(colorAmbient),
    colorDiffuse(colorAmbient),
    //colorSpecular(float4::black),
    //colorEmissive(float4::black),
    m_Ns(10.0f),
    typeOfMaterial(typeOfMaterial),
    m_n(n),
    diffuseReflectionCoefficient(float4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR)),
    specularReflectionCoefficient(float4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR))
{ }

Material::Material(std::string name, MaterialType typeOfMaterial, float n) :
    name(name),
    typeOfMaterial(typeOfMaterial),
    m_n(n),
    diffuseReflectionCoefficient(float4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR)),
    specularReflectionCoefficient(float4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR))
{ }

Material::Material(const Material &newMaterial) :
    name(newMaterial.Name()),
    colorAmbient(newMaterial.ColorAmbient()),
    colorDiffuse(newMaterial.ColorDiffuse()),
    colorSpecular(newMaterial.ColorSpecular()),
    colorEmissive(newMaterial.ColorEmissive()),
    m_n(newMaterial.N()),
    m_Ni(newMaterial.Ni()),
    m_Ns(newMaterial.Ns()),
    m_d(newMaterial.D()),
    m_Tr(newMaterial.Tr()),
    m_Tf(newMaterial.Tf()),
    illum(newMaterial.Illum()),
    //ambientTexture(newMaterial.AmbientTexture()),
    //diffuseTexture(newMaterial.DiffuseTexture()),
    //specularTexture(newMaterial.SpecularTexture()),
    typeOfMaterial(newMaterial.TypeOfMaterial()),
    diffuseReflectionCoefficient(newMaterial.DiffuseReflectionCoefficient()),
    specularReflectionCoefficient(newMaterial.SpecularReflectionCoefficient())
{ }

Material::~Material()
{ }

Material& Material::operator=(const Material &rhs)
{
    name = rhs.Name();
    colorAmbient = rhs.ColorAmbient();
    colorDiffuse = rhs.ColorDiffuse();
    colorSpecular = rhs.ColorSpecular();
    colorEmissive = rhs.ColorEmissive();
    m_n = rhs.N();
    m_Ni = rhs.Ni();
    m_Ns = rhs.Ns();
    m_d = rhs.D();
    m_Tr = rhs.Tr();
    m_Tf = rhs.Tf();
    illum = rhs.Illum();
    //ambientTexture = rhs.AmbientTexture();
    //diffuseTexture = rhs.DiffuseTexture();
    //specularTexture = rhs.SpecularTexture();
    typeOfMaterial = rhs.TypeOfMaterial();
    diffuseReflectionCoefficient = rhs.DiffuseReflectionCoefficient();
    specularReflectionCoefficient = rhs.SpecularReflectionCoefficient();

    return *this;
}
