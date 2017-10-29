// Renderer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TgaBuffer.h"


int main()
{	
	TgaBuffer buffer(1024, 1024);
	buffer.ClearColor();
	buffer.Save("test.tga");


	TgaBuffer buffer1;
	buffer1.ClearColor(0x00ffff00); /// ARGB
	buffer1.Save("test1.tga");

	system("pause");
    return 0;
}

