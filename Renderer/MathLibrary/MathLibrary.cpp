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

float& ClampSingle(const float &x, const float min, const float max)
{
    float new_x = x;
    if (new_x < min)
    {
        new_x = min;
    }
    else if (x > max)
    {
        new_x = max;
    }

    return new_x;
}

int Min(int v1, int v2, int v3)
{
    return std::min(v1, std::min(v2, v3));
}

int Max(int v1, int v2, int v3)
{
    return std::max(v1, std::max(v2, v3));
}

void ClampColor(float3 &value)
{
    ClampSingle(value.x, 0.0f, 1.0f);
    ClampSingle(value.y, 0.0f, 1.0f);
    ClampSingle(value.z, 0.0f, 1.0f);
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
float4x4 mul(const float4x4 & l, const float4x4 & r)
{
    float4x4 result{};

    /*for (int i = 0; i < 4; ++i)
    {
    for (int j = 0; j < 4; ++j)
    {
    result[i][j] = 0;
    for (int iter = 0; iter < 4; ++iter)
    {
    result[i][j] += l[iter][i] * r[j][iter];
    }
    }
    }*/

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result[i][j] = 0;
            for (int k = 0; k < 4; ++k)
            {
                result[i][j] += l[i][k] * r[k][j];
            }
        }
    }

    return result;
}

float4 mul(const float4x4 & l, const float4 & r)
{
    float4 result{};
    for (int i = 0; i < 4; ++i)
    {
        result[i] = 0.f;
        for (int j = 0; j < 4; ++j)
        {
            result[i] += l[i][j] * r[j];
        }
    }
    return result;
}
float3 UintToColor(uint color)
{
    return float3{
        (float)((color >> 16) % 256) / 256.f,
        (float)((color >> 8) % 256) / 256.f,
        (float)(color % 256) / 256.f
    };
}

