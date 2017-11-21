// Renderer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TgaBuffer.h"
#include "Rasterizer.h"
#include "Mesh.h"

static const int PIXEL_SIZE = 1024;

void TestInterpolation();
void RenderMesh();
void RenderMesh1();

int main()
{
    TestInterpolation();
    RenderMesh();
    RenderMesh1();

    system("pause");
    return 0;
}

void TestInterpolation()
{
    TgaBuffer buffer1 = TgaBuffer(PIXEL_SIZE, PIXEL_SIZE);
    buffer1.ClearColor(0x00000000); /// ARGB

                                    //cout << hex << ColorToUint(float3(1.0f, 0.0f, 0.0f)) << endl;

    Rasterizer rast = Rasterizer(&buffer1);
    rast.Triangle(
        float3(-1.0f, -0.5f, 0.0f),
        float3(-0.5f, 0.5f, 0.0f),
        float3(0.0f, -0.5f, 0.0f),
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 1.0f, 0.0f),
        float3(1.0f, 0.0f, 0.0f)
    );

    rast.Triangle(
        float3(0.0f, -0.5f, 0.0f),
        float3(-0.5f, 0.5f, 0.0f),
        float3(0.5f, 0.5f, 0.0f),
        float3(1.0f, 0.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f)
    );

    rast.Triangle(
        float3(0.0f, -0.5f, 0.0f),
        float3(0.5f, 0.5f, 0.0f),
        float3(1.0f, -0.5f, 0.0f),
        float3(1.0f, 0.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f),
        float3(0.0f, 0.0f, 1.0f)
    );

    buffer1.Save("test1.tga");
}

void RenderMesh()
{
    TgaBuffer buffer2 = TgaBuffer(PIXEL_SIZE, PIXEL_SIZE);
    buffer2.ClearColor(0x00000000); /// ARGB
    Rasterizer rast2 = Rasterizer(&buffer2);
    VertexProcessor vp = VertexProcessor();
    //vp.SetPerspective(60, (static_cast<float>(PIXEL_SIZE) / static_cast<float>(PIXEL_SIZE)), 0.01f, 100000.0f);
    vp.SetPerspective(60, 1.0f, 0.00001f, 100000000.0f);
    vp.SetLookAt(float3(0.0f, 0.0f, 100.0f), float3::zero, float3::up);

    //Mesh msh2 = Mesh();
    //msh2.polygons.push_back(Triangle(float3(-0.5f, -0.5f, 0.5f), float3(-0.5f, -0.5f, -0.5f), float3(0.5f, -0.5f, -0.5f)));
    //msh2.polygons.push_back(Triangle(float3(0.1784f, -1.8745f, 0.7996f), float3(-0.7412f, -1.4875f, 0.1675f), float3(0.0000f, -1.0073f, -0.6167f)));
    Mesh msh = Mesh("cube", 1.0f);
    //vp.Scale(float3(0.0001f));
    vp.calculateFinalMatrixAkaTransform();
    msh.Draw(rast2, vp);
    //msh2.Draw(rast2, vp);

    buffer2.Save("test2.tga");
}

void RenderMesh1()
{
    int width = 1280;
    int height = 720;
    TgaBuffer buffer(width, height);
    buffer.ClearColor();
    Rasterizer rasterizer(&buffer);

    VertexProcessor vp = VertexProcessor();

    //vp.Scale(float3(2.0F));
    //vp.Rotate(15.0F, float3::forward);
    //vp.Translate(float3(0.0F, -0.5F, 0.0F));

    vp.SetLookAt(float3(0.0F, 0.0F, 4.0F), float3::zero, float3::up);

    vp.SetPerspective(60.0F, static_cast<float>(width) / height, 0.3F, 100.0F);

    vp.calculateFinalMatrixAkaTransform();

    rasterizer.Triangle(vp.tr(float3(-0.5F, -0.5F, 0.0F)), vp.tr(float3(0.0F, 0.5F, 0.0F)), vp.tr(float3(0.5F, -0.5F, 0.0F)),
        float3(1.0f, 0.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f),
        float3(0.0f, 0.0f, 1.0f));

    buffer.Save("Test3.tga");
}
