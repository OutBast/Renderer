#include "stdafx.h"
#include "float3.h"

float3 float3::back = float3(0, 0, -1);
float3 float3::down = float3(0, -1, 0);
float3 float3::forward = float3(0, 0, 1);
float3 float3::left = float3(-1, 0, 0);
float3 float3::right = float3(1, 0, 0);
float3 float3::up = float3(0, 1, 0);
float3 float3::zero = float3(0, 0, 0);
float3 float3::one = float3(1, 1, 1);

float3::float3() :
	x(0.0f),
	y(0.0f),
	z(0.0f)
{ }

float3::float3(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{ }

float3::float3(int x, int y, int z) :
	x(static_cast<float>(x)),
	y(static_cast<float>(y)),
	z(static_cast<float>(z))
{ }

float3::float3(float x, float y) :
	x(x),
	y(y),
	z(0.0f)
{ }

float3::float3(const float3 &value) : x(value.x), y(value.y), z(value.z)
{ }

float3::~float3()
{ }

float float3::Magnitude()
{
	return sqrt(sqr(x) + sqr(y) + sqr(z));
}

float float3::Magnitude(float3 &value)
{
	return sqrt(sqr(value.x) + sqr(value.y) + sqr(value.z));
}

float float3::SqrMagnitude()
{
	return sqr(x) + sqr(y) + sqr(z);
}

float float3::SqrMagnitude(float3 &value)
{
	return sqr(value.x) + sqr(value.y) + sqr(value.z);
}

void float3::Normalize()
{
	float length = Magnitude();

	x /= length;
	y /= length;
	z /= length;
}

float3 float3::Normalize(float3 &value)
{
	float length = Magnitude(value);

	value.x /= length;
	value.y /= length;
	value.z /= length;

	return value;
}

float3 float3::Reflect(float3 &normal)
{
	float3 reflectedVector;
	reflectedVector = 2.0f * Dot(normal) * normal;
	reflectedVector = *this - reflectedVector;
	return reflectedVector;
}

float3 float3::Reflect(float3 &direction, float3 &normal)
{
	return float3(direction - (2.0f * Dot(direction, normal) * normal));
}

float3 float3::Refract(float inFactor, float outFactor, float3 direction, float3 normal)
{
	float n = inFactor / outFactor;
	float dotDN = Dot(direction, normal);

	float3 result;
	result = n * direction + (n * dotDN - sqrt(1.0f - sqr(n) * (1.0f - sqr(dotDN)))) * normal;
	return result;
}

void float3::Reverse()
{
	x = -x;
	y = -y;
	z = -z;
}

float3 float3::Reverse(const float3 &value)
{
	float3 result = float3::zero;

	result.x = -value.x;
	result.y = -value.y;
	result.z = -value.z;

	return result;
}

float3 float3::Normalized()
{
	return Normalize(*this);
}

void float3::Scale(float3 scale)
{
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
}

void float3::Set(float new_x, float new_y, float new_z)
{
	x = new_x;
	y = new_y;
	z = new_z;
}

float float3::Angle(float3 &from, float3 &to)
{

	return RadiansToDegrees(acos(Dot(from, to) / (from.Magnitude() * to.Magnitude())));
}

float float3::Angle(float3 &rhs)
{
	return RadiansToDegrees(acos(Dot(rhs) / (Magnitude() * rhs.Magnitude())));
}

float3 float3::Cross(float3 &a, float3 &b)
{
	return float3((a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x));
}

float3 float3::Cross(float3 &rhs)
{
	return float3((y * rhs.z - z * rhs.y), (z * rhs.x - x * rhs.z), (x * rhs.y - y * rhs.x));
}

float float3::Distance(float3 &from, float3 &to)
{
	return sqrt(sqr(from.x - to.x) + sqr(from.y - to.y) + sqr(from.z - to.z));
}

float float3::Distance(float3 &rhs)
{
	return sqrt(sqr(x - rhs.x) + sqr(y - rhs.y) + sqr(z - rhs.z));
}

float float3::Dot(float3 &a, float3 &b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

float float3::Dot(float3 &rhs)
{
	return ((x * rhs.x) + (y * rhs.y) + (z * rhs.z));
}

float3& float3::operator=(const float3 &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

float3& float3::operator/=(const float3 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;

	return *this;
}

float3& float3::operator*=(const float3 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

float3& float3::operator-=(const float3 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

float3 float3::operator-() const
{
	float3 value;

	value.x = -x;
	value.y = -y;
	value.z = -z;

	return value;
}

float3& float3::operator+=(const float3 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

float3 operator+(const float3 &lhs, const float3 &rhs)
{
	float3 result = lhs;

	result += rhs;

	return result;
}

float3 operator-(const float3 &lhs, const float3 &rhs)
{
	float3 result = lhs;

	result -= rhs;

	return result;
}

float3 operator-(const float3 &lhs, const float &rhs)
{
	float3 result;

	result.X(lhs.X() - rhs);
	result.Y(lhs.Y() - rhs);
	result.Z(lhs.Z() - rhs);

	return result;
}

float3 operator*(const float3 &lhs, const float3 &rhs)
{
	float3 result = lhs;

	result *= rhs;

	return result;
}

float3 operator/(const float3 &lhs, const float3 &rhs)
{
	float3 result = lhs;

	result /= rhs;

	return result;
}

std::ostream & operator<<(std::ostream &os, const float3 &value)
{
	os << "(" << value.x << ", " << value.y << ", " << value.z << ")";

	return os;
}

std::istream & operator >> (std::istream &is, float3 &value)
{
	is >> value.x >> value.y >> value.z;

	return is;
}

bool operator==(const float3 &lhs, const float3 &rhs)
{
	bool result = false;
	if (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z)
	{
		result = true;
	}

	return result;
}

bool operator!=(const float3 &lhs, const float3 &rhs)
{
	return !(lhs == rhs);
}

float3& float3::operator*=(const float &rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}

float3& float3::operator/=(const float &rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;

	return *this;
}

float3 operator*(const float3 &lhs, const float& rhs)
{
	float3 result = lhs;

	result *= rhs;

	return result;
}

float3 operator*(const float& lhs, const float3 &rhs)
{
	float3 result = rhs;

	result *= lhs;

	return result;
}

float3 operator/(const float3 &lhs, const float& rhs)
{
	float3 result = lhs;

	result /= rhs;

	return result;
}