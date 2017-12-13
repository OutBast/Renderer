#include "stdafx.h"
#include "Mesh.h"
#include <thread>

using namespace std;

Mesh::Mesh() : Primitive()
{ }

Mesh::Mesh(const std::string &fileName, MaterialType typeOfMaterial, const float &scale, const float &n) :
    Primitive(new Material(fileName, typeOfMaterial, n))
{
    LoadMesh(fileName, scale);
}

Mesh::Mesh(const Mesh &mesh) :
    polygons(mesh.Polygons())
{ }


Mesh::Mesh(const std::string &fileName, float scale) : Primitive()
{
    LoadMesh(fileName, scale);
}

Mesh::~Mesh()
{
}

void Mesh::LoadMesh(const std::string &fileName, const float &scale)
{
    string token;
    string stringValue;
    ifstream objFile(fileName + ".obj");
    ifstream mtlFile(fileName + ".mtl");

    float3 vectorValue;
    char delimeter = ' ';
    vector<string> objFileTokens;
    vector<string> mtlFileTokens;

    if (mtlFile.is_open())
    {
        while (mtlFile >> token)
        {
            mtlFileTokens.push_back(token);
        }

        mtlFile.close();
    }
    else
    {
        cout << "Unable to open file: " << fileName << ".mtl" << endl;
    }

    if (objFile.is_open())
    {
        while (objFile >> token)
        {
            objFileTokens.push_back(token);
        }

        objFile.close();
    }
    else
    {
        cout << "Unable to open file: " << fileName << ".obj" << endl;
    }

    Material *currentMat = new Material();
    size_t count = mtlFileTokens.size();
    int i = 0;
    while (i < count)
    {
        if (mtlFileTokens[i] == "newmtl")
        {
            materials.push_back(Material(mtlFileTokens[i + 1], currentMat->TypeOfMaterial(), currentMat->N()));
            currentMat = &materials[materials.size() - 1];
            i += 2;
            continue;
        }

        if (mtlFileTokens[i] == "Ns")
        {
            currentMat->Ns(stof(mtlFileTokens[i + 1]));
            i += 2;
            continue;
        }
        if (mtlFileTokens[i] == "Ni")
        {
            currentMat->Ni(stof(mtlFileTokens[i + 1]));
            i += 2;
            continue;
        }
        if (mtlFileTokens[i] == "d")
        {
            currentMat->D(stof(mtlFileTokens[i + 1]));
            i += 2;
            continue;
        }
        if (mtlFileTokens[i] == "Tr")
        {
            currentMat->Tr(stof(mtlFileTokens[i + 1]));
            i += 2;
            continue;
        }
        if (mtlFileTokens[i] == "Tf")
        {
            currentMat->Tf(float3(stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3])));
            i += 4;
            continue;
        }
        if (mtlFileTokens[i] == "illum")
        {
            currentMat->Illum(stof(mtlFileTokens[i + 1]));
            i += 2;
            continue;
        }
        if (mtlFileTokens[i] == "Ka")
        {
            currentMat->ColorAmbient(float4(stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3])));
            i += 4;
            continue;
        }
        if (mtlFileTokens[i] == "Kd")
        {
            currentMat->ColorDiffuse(float4(stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3])));
            i += 4;
            continue;
        }
        if (mtlFileTokens[i] == "Ks")
        {
            currentMat->ColorSpecular(float4(stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3])));
            i += 4;
            continue;
        }
        if (mtlFileTokens[i] == "Ke")
        {
            currentMat->ColorEmissive(float4(stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3])));
            i += 4;
            continue;
        }

        //TEXTURES
        if (mtlFileTokens[i] == "map_Ka")
        {
            currentMat->AmbientTexture(Texture(512, 512, mtlFileTokens[i + 1]));
            i += 2;
        }
        if (mtlFileTokens[i] == "map_Kd")
        {
            currentMat->DiffuseTexture(Texture(512, 512, mtlFileTokens[i + 1]));
            i += 2;
        }
        //if (mtlFileTokens[i] == "map_Ks")
        //{
        //    currentMat->SpecularTexture(Texture(512, 512, mtlFileTokens[i + 1]));
        //    i += 2;
        //}


        ++i;
    }


    count = objFileTokens.size();
    i = 0;

    while (i < count)
    {
        if (objFileTokens[i] == "v")
        {
            vertices.push_back(float3(stof(objFileTokens[i + 1]), stof(objFileTokens[i + 2]), stof(objFileTokens[i + 3])));
            i += 4;
            continue;
        }

        if (objFileTokens[i] == "vn")
        {
            normals.push_back(float3(stof(objFileTokens[i + 1]), stof(objFileTokens[i + 2]), stof(objFileTokens[i + 3])));
            i += 4;
            continue;
        }

        if (objFileTokens[i] == "vt")
        {
            textureCoord.push_back(float3(stof(objFileTokens[i + 1]), stof(objFileTokens[i + 2]), stof(objFileTokens[i + 3])));
            i += 4;
            continue;
        }

        if (objFileTokens[i] == "usemtl")
        {
            for (Material &mat : materials)
            {
                if (mat.Name() == objFileTokens[i + 1])
                {
                    currentMat = &mat;
                }
            }
        }

        if (objFileTokens[i] == "f")
        {
            size_t first = objFileTokens[i + 1].find_first_of('/');
            size_t last = objFileTokens[i + 1].find_last_of('/');

            string sub = objFileTokens[i + 1].substr(0, first);
            int index1 = stoi(sub) - 1;

            first = objFileTokens[i + 2].find_first_of('/');
            sub = objFileTokens[i + 2].substr(0, first);
            int index2 = stoi(sub) - 1;

            first = objFileTokens[i + 3].find_first_of('/');
            sub = objFileTokens[i + 3].substr(0, first);
            int index3 = stoi(sub) - 1;

            sub = objFileTokens[i + 1].substr(++last, objFileTokens[i + 1].size());
            int index4 = stoi(sub) - 1;

            first = objFileTokens[i + 1].find_first_of('/');
            last = objFileTokens[i + 1].find_last_of('/');
            sub = objFileTokens[i + 1].substr(++first, last);
            int index5 = stoi(sub) - 1;

            first = objFileTokens[i + 2].find_first_of('/');
            last = objFileTokens[i + 2].find_last_of('/');
            sub = objFileTokens[i + 2].substr(++first, last);
            int index6 = stoi(sub) - 1;

            first = objFileTokens[i + 3].find_first_of('/');
            last = objFileTokens[i + 3].find_last_of('/');
            sub = objFileTokens[i + 3].substr(++first, last);
            int index7 = stoi(sub) - 1;

            //polygons.push_back(Triangle(vertices[index1], vertices[index2], vertices[index3], normals[index4], *currentMat));
            polygons.push_back(Triangle(vertices[index2], vertices[index1], vertices[index3], normals[index4], *currentMat, textureCoord[index5], textureCoord[index6], textureCoord[index7]));
            i += 4;
            continue;
        }

        ++i;
    }

    float minX = 0.0f, minY = 0.0f, minZ = 0.0f, maxX = 0.0f, maxY = 0.0f, maxZ = 0.0f;

    for (auto &vertex : vertices)
    {
        if (vertex.X() < minX)
        {
            minX = vertex.X();
        }

        if (vertex.Y() < minY)
        {
            minY = vertex.Y();
        }

        if (vertex.Z() < minZ)
        {
            minZ = vertex.Z();
        }

        if (vertex.X() > maxX)
        {
            maxX = vertex.X();
        }

        if (vertex.Y() > maxY)
        {
            maxY = vertex.Y();
        }

        if (vertex.Z() > maxZ)
        {
            maxZ = vertex.Z();
        }
    }

    float halfX = (maxX - minX) * 0.5f;
    float halfY = (maxY - minY) * 0.5f;
    float halfZ = (maxZ - minZ) * 0.5f;

    center = float3(minX + halfX, minY + halfY, minZ + halfZ);

    float radius = 0.0f;
    float distance = 0.0f;
    for (auto &vertex : vertices)
    {
        distance = float3::Distance(vertex, center);
        if (distance > radius)
        {
            radius = distance;
        }
    }
}

void Mesh::Draw(Rasterizer& r, VertexProcessor& vp)
{
    for (auto &triangle : polygons)
    {
        triangle.Draw(r, vp);
    }
}

Primitive* Mesh::Clone() const
{
    return new Mesh(*this);
}