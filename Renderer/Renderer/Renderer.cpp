// Renderer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TgaBuffer.h"
#include "Rasterizer.h"


int main()
{
    TgaBuffer buffer1 = TgaBuffer(1024, 1024);
    buffer1.ClearColor(0x00000000); /// ARGB

    cout << hex << ColorToUint(float3(1.0f, 0.0f, 0.0f)) << endl;

    Rasterizer rast = Rasterizer(&buffer1);
    rast.Triangle(float3(-1.0f, -0.5f, 0.0f),
                  float3(-0.5f, 0.5f, 0.0f),
                  float3(0.0f, -0.5f, 0.0f),
                  float3(0.0f, 0.0f, 1.0f),
                  float3(0.0f, 1.0f, 0.0f),
                  float3(1.0f, 0.0f, 0.0f));

    rast.Triangle(float3(0.0f, -0.5f, 0.0f),
                  float3(-0.5f, 0.5f, 0.0f),
                  float3(0.5f, 0.5f, 0.0f),
                  float3(1.0f, 0.0f, 0.0f),
                  float3(0.0f, 1.0f, 0.0f),
                  float3(0.0f, 1.0f, 0.0f));

    rast.Triangle(float3(0.0f, -0.5f, 0.0f),
                  float3(0.5f, 0.5f, 0.0f),
                  float3(1.0f, -0.5f, 0.0f),
                  float3(1.0f, 0.0f, 0.0f),
                  float3(0.0f, 1.0f, 0.0f),
                  float3(0.0f, 0.0f, 1.0f));

    buffer1.Save("test1.tga");

    system("pause");
    return 0;
}