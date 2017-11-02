#include "stdafx.h"
#include "MathLibrary.h"
#include "float3.h"
#include "float4.h"

float& ClampSingle(float &x, const float min, const float max)
{
	if (x < min)
	{
		x = min;
	}
	else if (x > max)
	{
		x = max;
	}

	return x;
}

float DegreesToRadians(const float& degrees)
{
	return (static_cast<float>(degrees * M_PI) / 180.0f);
}

float RadiansToDegrees(const float& radians)
{
	return radians * 180.0f / static_cast<float>(M_PI);
}

float Maximum(const float &r, const float &g, const float &b)
{
	float max = r;

	if (g > max)
	{
		max = g;
	}

	if (b > max)
	{
		max = b;
	}

	return max;
}

uint ColorToUint(const float3& color)
{
    return (uint)((0 * COLOR_MAX << 24) | ((int)ceilf(color.R() * COLOR_MAX) << 16) | (((int)ceilf(color.G() * COLOR_MAX) << 8) | (int)ceilf(color.B() * COLOR_MAX)));
}

uint ColorToUint(const float4& color)
{
    return (uint)(((int)ceilf(color.R() * COLOR_MAX) << 24) | ((int)ceilf(color.R() * COLOR_MAX) << 16) | (((int)ceilf(color.G() * COLOR_MAX) << 8) | (int)ceilf(color.B() * COLOR_MAX)));
}

float3 UintToColor(uint color)
{
    return float3();
}

