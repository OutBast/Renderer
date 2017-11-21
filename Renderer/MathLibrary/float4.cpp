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

float4::float4(const float3& val, float w) : x(val.X()), y(val.Y()), z(val.Z()), w(w)
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

float4& float4::operator-=(const float4 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;

    return *this;
}

float4 float4::operator-() const
{
    float4 result;

    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;

    return result;
}

float4& float4::operator-=(const float &rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    w -= rhs;

    return *this;
}

float4& float4::operator+=(const float &rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    w += rhs;

    return *this;
}

float4& float4::operator/=(const float &rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;

    return *this;
}

float4& float4::operator*=(const float &rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;

    return *this;
}

float4& float4::operator/=(const float4 &rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;

    return *this;
}

float4& float4::operator*=(const float4 &rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;

    return *this;
}

float4& float4::operator+=(const float4 &rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;

    return *this;
}

float4& float4::operator=(const float4 &rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;

    return *this;
}

float4 operator+(const float4 &lhs, const float4 &rhs)
{
    float4 result = lhs;

    result += rhs;

    return result;
}

float4 operator-(const float4 &lhs, const float4 &rhs)
{
    float4 result = lhs;

    result -= rhs;

    return result;
}

float4 operator-(const float4 &lhs, const float &rhs)
{
    float4 result = lhs;

    result += rhs;

    return result;
}

float4 operator*(const float4 &lhs, const float4 &rhs)
{
    float4 result = lhs;

    result *= rhs;

    return result;
}

float4 operator*(const float4 &lhs, const float &rhs)
{
    float4 result = lhs;

    result *= rhs;

    return result;
}

float4 operator*(const float &lhs, const float4 &rhs)
{
    float4 result = rhs;

    result *= lhs;

    return result;
}

float4 operator/(const float4 &lhs, const float4 &rhs)
{
    float4 result = lhs;

    result /= rhs;

    return result;
}

float4 operator/(const float4 &lhs, const float &rhs)
{
    float4 result = lhs;

    result /= rhs;

    return result;

}

bool operator==(const float4 &lhs, const float4 &rhs)
{
    bool result = false;
    if (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w)
    {
        result = true;
    }

    return result;

}

std::ostream &operator<<(std::ostream &os, const float4 &value)
{
    os << "(" << value.x << ", " << value.y << ", " << value.z << ", " << value.w << ")";

    return os;

}
std::istream &operator >> (std::istream &is, float4 &value)
{
    is >> value.x >> value.y >> value.z >> value.w;

    return is;

}

bool operator!=(const float4 &lhs, const float4 &rhs)
{
    return !(lhs == rhs);
}
