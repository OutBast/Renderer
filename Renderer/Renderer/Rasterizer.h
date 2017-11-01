#pragma once
#include "Buffer.h"

class Rasterizer
{
public:
	Rasterizer(Buffer* buff);
	~Rasterizer();

	void Triangle(const float3& v1, const float3& v2, const float3& v3,
				  uint c1, uint c2, uint c3);

private:
	float TransformNDCSpaceToScreenSpace(float v, int offset);

	Buffer* buffer;
};

