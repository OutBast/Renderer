// Renderer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TgaBuffer.h"
#include "Rasterizer.h"
#include "Mesh.h"
#include "Data.h"
#include "DirectionalLight.h"

static const int PIXEL_SIZE = 1024;

void TestInterpolation();
void RenderMesh();
void RenderMesh1();
void RenderMesh4();

int main()
{
    //TestInterpolation();
    //RenderMesh();
    //RenderMesh1();
    RenderMesh4();

    system("pause");
    return 0;
}
//
//void TestInterpolation()
//{
//    TgaBuffer buffer1 = TgaBuffer(PIXEL_SIZE, PIXEL_SIZE);
//    buffer1.ClearColor(0x00000000); /// ARGB
//    buffer1.ClearDepth();
//
//                                    //cout << hex << ColorToUint(float3(1.0f, 0.0f, 0.0f)) << endl;
//
//    Rasterizer rast = Rasterizer(&buffer1);
//    rast.Triangle(
//        float3(-1.0f, -0.5f, 0.0f),
//        float3(-0.5f, 0.5f, 0.0f),
//        float3(0.0f, -0.5f, 0.0f),
//        float3(0.0f, 0.0f, 1.0f),
//        float3(0.0f, 1.0f, 0.0f),
//        float3(1.0f, 0.0f, 0.0f)
//    );
//
//    rast.Triangle(
//        float3(0.0f, -0.5f, 0.0f),
//        float3(-0.5f, 0.5f, 0.0f),
//        float3(0.5f, 0.5f, 0.0f),
//        float3(1.0f, 0.0f, 0.0f),
//        float3(0.0f, 1.0f, 0.0f),
//        float3(0.0f, 1.0f, 0.0f)
//    );
//
//    rast.Triangle(
//        float3(0.0f, -0.5f, 0.0f),
//        float3(0.5f, 0.5f, 0.0f),
//        float3(1.0f, -0.5f, 0.0f),
//        float3(1.0f, 0.0f, 0.0f),
//        float3(0.0f, 1.0f, 0.0f),
//        float3(0.0f, 0.0f, 1.0f)
//    );
//
//    buffer1.Save("test1.tga");
//}
//
//void RenderMesh()
//{
//    int width = 1024;
//    int height = 1024;
//    TgaBuffer buffer2 = TgaBuffer(width, height);
//    buffer2.ClearColor(0x00000000); /// ARGB
//    buffer2.ClearDepth();
//    Rasterizer rast2 = Rasterizer(&buffer2);
//    VertexProcessor vp = VertexProcessor();
//    vp.SetPerspective(60.0F, static_cast<float>(width) / height, 0.3F, 100.0F);
//    vp.SetLookAt(float3(3.0f, 3.0f, 3.0f), float3::zero, float3::up);
//
//    Mesh msh = Mesh("cube", 1.0f);
//    vp.calculateFinalMatrixAkaTransform();
//    msh.Draw(rast2, vp);
//
//    buffer2.Save("test2.tga");
//}
//
//void RenderMesh1()
//{
//    int width = 1280;
//    int height = 720;
//    TgaBuffer buffer(width, height);
//    buffer.ClearColor();
//    buffer.ClearDepth();
//    Rasterizer rasterizer(&buffer);
//
//    VertexProcessor vp = VertexProcessor();
//
//    vp.Scale(float3(2.0F));
//    vp.Rotate(float3::forward, 15.0F);
//    vp.Translate(float3(0.0F, -0.5F, 0.0F));
//
//    vp.SetLookAt(float3(0.0F, 0.0F, 4.0F), float3::zero, float3::up);
//
//    vp.SetPerspective(60.0F, static_cast<float>(width) / height, 0.3F, 100.0F);
//
//    vp.calculateFinalMatrixAkaTransform();
//
//    rasterizer.Triangle(vp.tr(float3(-0.5F, -0.5F, 0.0F)), vp.tr(float3(0.0F, 0.5F, 0.0F)), vp.tr(float3(0.5F, -0.5F, 0.0F)),
//        float3(1.0f, 0.0f, 0.0f),
//        float3(0.0f, 1.0f, 0.0f),
//        float3(0.0f, 0.0f, 1.0f));
//
//    buffer.Save("Test3.tga");
//}

void RenderMesh4()
{
    int width = 512;
    int height = 512;
    TgaBuffer buffer2 = TgaBuffer(width, height);
    buffer2.ClearColor(0x0000000); /// ARGB
    buffer2.ClearDepth();
    Rasterizer rast2 = Rasterizer(&buffer2);
    VertexProcessor vp = VertexProcessor();

    Data::Instance().AmbientLight() = { 0.4f, 0.4f, 0.4f };
    DirectionalLight *light = new DirectionalLight(&vp,{ 0.1f, 1.0f, -1.0f },{ 1, 0, 0 },{ 0.1f, 0.1f, 0.1f });

    vp.SetPerspective(60.0F, static_cast<float>(width) / height, 0.3F, 100.0F);
    vp.SetLookAt(float3(3.0f, 3.0f, 3.0f), float3::zero, float3::up);

    Mesh msh1 = Mesh("teapot", 1.0f);
    Mesh msh2 = Mesh("sphere", 1.0f);
    Mesh msh3 = Mesh("plane", 1.0f);
    Mesh msh4 = Mesh("torus", 1.0f);
    Mesh msh5 = Mesh("cone", 1.0f);
    Mesh msh6 = Mesh("cylinder", 1.0f);
    Mesh msh7 = Mesh("cube", 1.0f);
    vp.calculateFinalMatrixAkaTransform();
    msh1.Draw(rast2, vp);
    msh2.Draw(rast2, vp);
    msh3.Draw(rast2, vp);
    msh4.Draw(rast2, vp);
    msh5.Draw(rast2, vp);
    msh6.Draw(rast2, vp);
    msh7.Draw(rast2, vp);

    buffer2.Save("test4.tga");
}
