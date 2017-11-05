#include "stdafx.h"
#include "float3.h"
#include "float4.h"


float4::float4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{ }

float4::float4(float value) : x(value), y(value), z(value), w(1.0f)
{}

float4::float4(float x, float y, float z) : x(x), y(y), z(z), w(1.0f)
{ }

float4::float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{ }

float4::float4(const float3& val) : x(val.X()), y(val.Y()), z(val.Z()), w(1.0f)
{ }

float4::~float4()
{ }

float float4::Dot(float4 &a, float4 &b)
{
    return ((a.X() * b.X()) + (a.Y() * b.Y()) + (a.Z() * b.Z()) + (a.W() * b.W()));
}

float float4::Dot(float4 &rhs)
{
    return ((x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w));
}
