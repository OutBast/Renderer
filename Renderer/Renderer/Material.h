#pragma once

#include "float3.h"
#include "Texture.h"

enum class MaterialType
{
    MATTE = 1,
    REFLECTIVE = 2,
    REFRACTIVE = 3
};

class Material
{
public:
    Material();
    Material(std::string name, MaterialType typeOfMaterial, float n);
    Material(const float4 &colorAmbient, MaterialType typeOfMaterial, float n);
    Material(const Material &newMaterial);
    ~Material();


    Material& operator=(const Material &rhs);


    std::string Name() const { return name; }
    void Name(std::string val) { name = val; }
    float4 ColorAmbient() const { return colorAmbient; }
    void ColorAmbient(float4 val) { colorAmbient = val; }
    float4 ColorDiffuse() const { return colorDiffuse; }
    void ColorDiffuse(float4 val) { colorDiffuse = val; }
    float4 ColorSpecular() const { return colorSpecular; }
    void ColorSpecular(float4 val) { colorSpecular = val; }
    float4 ColorEmissive() const { return colorEmissive; }
    void ColorEmissive(float4 val) { colorEmissive = val; }
    float Ns() const { return m_Ns; }
    void Ns(float val) { m_Ns = val; }
    float Ni() const { return m_Ni; }
    void Ni(float val) { m_Ni = val; }
    float D() const { return m_d; }
    void D(float val) { m_d = val; }
    float Tr() const { return m_Tr; }
    void Tr(float val) { m_Tr = val; }
    float3 Tf() const { return m_Tf; }
    void Tf(float3 val) { m_Tf = val; }
    float Illum() const { return illum; }
    void Illum(float val) { illum = val; }
    Texture AmbientTexture() const { return ambientTexture; }
    void AmbientTexture(Texture val) { ambientTexture = val; }
    Texture DiffuseTexture() const { return diffuseTexture; }
    void DiffuseTexture(Texture val) { diffuseTexture = val; }
    Texture SpecularTexture() const { return specularTexture; }
    void SpecularTexture(Texture val) { specularTexture = val; }
    float N() const { return m_n; }
    void N(float val) { m_n = val; }
    MaterialType TypeOfMaterial() const { return typeOfMaterial; }
    void TypeOfMaterial(MaterialType val) { typeOfMaterial = val; }
    float4 DiffuseReflectionCoefficient() const { return diffuseReflectionCoefficient; }
    void DiffuseReflectionCoefficient(float4 val) { diffuseReflectionCoefficient = val; }
    float4 SpecularReflectionCoefficient() const { return specularReflectionCoefficient; }
    void SpecularReflectionCoefficient(float4 val) { specularReflectionCoefficient = val; }
private:
    string name;
    float4 colorAmbient;
    float4 colorDiffuse;
    float4 colorSpecular;
    float4 colorEmissive;
    float m_Ns;					// Specular Highlight
    float m_Ni;
    float m_d;
    float m_Tr;
    float3 m_Tf;
    float illum;
    Texture ambientTexture;
    Texture diffuseTexture;
    Texture specularTexture;


    float m_n;
    MaterialType typeOfMaterial;

    float4 diffuseReflectionCoefficient;
    float4 specularReflectionCoefficient;
};

