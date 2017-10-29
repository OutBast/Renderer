#pragma once

#define EPSILON 0.000001f
#define REFLECT_BIAS 0.01f
#define REFRACT_BIAS 11.01f

typedef unsigned short ushort;
typedef unsigned int uint;

float& ClampSingle(float &x, const float min, const float max);
float DegreesToRadians(const float& degrees);
float RadiansToDegrees(const float& radians);
float Maximum(const float &r, const float &g, const float &b);

template<typename T>
inline T sqr(T x)
{
	return (x * x);
}