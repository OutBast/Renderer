#pragma once

#define EPSILON 0.000001f
#define REFLECT_BIAS 0.01f
#define REFRACT_BIAS 11.01f

class float3;
class float4;

typedef unsigned short ushort;
typedef unsigned int uint;

static const int COLOR_MAX = 255;

float& ClampSingle(float &x, const float min, const float max);
float DegreesToRadians(const float& degrees);
float RadiansToDegrees(const float& radians);
float Maximum(const float &r, const float &g, const float &b);

uint ColorToUint(const float3& color);
float3 UintToColor(uint color);
uint ColorToUint(const float4& color);

template<typename T>
inline T sqr(T x)
{
	return (x * x);
}