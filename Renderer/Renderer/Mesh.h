#pragma once

#include "Primitive.h"
#include "Triangle.h"
#include "Material.h"

class Mesh :
    public Primitive
{
public:
    Mesh();
    Mesh(const Mesh &mesh);
    Mesh(const std::string &fileName, MaterialType typeOfMaterial, const float &scale, const float &n);
    ~Mesh();

    void LoadMesh(const std::string &fileName, const float &scale);


    std::vector<float3> Vertices() const { return vertices; }
    void Vertices(std::vector<float3> val) { vertices = val; }
    std::vector<float3> TextureCoord() const { return textureCoord; }
    void TextureCoord(std::vector<float3> val) { textureCoord = val; }
    std::vector<float3> Normals() const { return normals; }
    void Normals(std::vector<float3> val) { normals = val; }

    virtual bool Intersect(Ray &ray, bool photon = false);
    virtual void IntersectionOutput(const Ray &ray);


    virtual Primitive* Clone() const override;

    std::vector<Triangle> Polygons() const { return polygons; }
    void Polygons(std::vector<Triangle> val) { polygons = val; }

    virtual float3 LocalIntersectionPoint(const float3 &worldIntersectionPoint, const float& scale) override;


    virtual float3 GetUVW(const float3& globalIntersectionPoint) override;

private:
    std::vector<Triangle> polygons;
    std::vector<float3> vertices;
    std::vector<float3> textureCoord;
    std::vector<float3> normals;
    std::vector<Material> materials;

    Triangle *intersectedTriangle;
};

