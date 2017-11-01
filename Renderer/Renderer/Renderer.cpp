// Renderer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TgaBuffer.h"
#include "Rasterizer.h"


int main()
{	
	TgaBuffer buffer1 = TgaBuffer(512, 512);
	buffer1.ClearColor(0x00000000); /// ARGB

	Rasterizer rast = Rasterizer(&buffer1);
	rast.Triangle(float3(-0.5f, -0.5f, 0.0f),
				  float3(0.0f, 0.5f, 0.0f),
				  float3(0.5f, -0.5f, 0.0f),
				  0x00ff0000,
			      0x0000ff00,
				  0x000000ff);

	buffer1.Save("test1.tga");

	system("pause");
    return 0;
}

