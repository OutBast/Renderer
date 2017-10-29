#include "stdafx.h"
#include "MathLibrary.h"

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

