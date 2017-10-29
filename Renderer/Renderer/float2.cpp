#include "stdafx.h"
#include "float2.h"

float2 float2::down = float2(0, -1);
float2 float2::left = float2(-1, 0);
float2 float2::right = float2(1, 0);
float2 float2::up = float2(0, 1);
float2 float2::zero = float2(0, 0);
float2 float2::one = float2(1, 1);

float2::float2() :
	x(0.0f),
	y(0.0f)
{ }

float2::float2(float x, float y) :
	x(x),
	y(y)
{ }

float2::float2(const float2 &value) :
	x(value.x),
	y(value.y)
{ }

float2::~float2()
{ }

double float2::Angle(float2 &rhs)
{
	return acos(Dot(rhs) / (Magnitude() * rhs.Magnitude())) * 180.0f / M_PI;
}

double float2::Angle(float2 &from, float2 &to)
{
	return acos(Dot(from, to) / (from.Magnitude() * to.Magnitude())) * 180.0f / M_PI;
}

float float2::Distance(float2 &rhs)
{
	return sqrt(sqr(x - rhs.x) + sqr(y - rhs.y));
}

float float2::Distance(float2 &from, float2 &to)
{
	return sqrt(sqr(from.x - to.x) + sqr(from.y - to.y));
}

float float2::Dot(float2 &rhs)
{
	return ((x * rhs.x) + (y * rhs.y));
}

float float2::Dot(float2 &a, float2 &b)
{
	return ((a.x * b.x) + (a.y * b.y));
}

float float2::Magnitude()
{
	return sqrt(sqr(x) + sqr(y));
}

float float2::Magnitude(float2 &value)
{
	return sqrt(sqr(value.x) + sqr(value.y));
}

float float2::SqrMagnitude()
{
	return sqr(x) + sqr(y);
}

float float2::SqrMagnitude(float2 &value)
{
	return sqr(value.x) + sqr(value.y);
}

void float2::Normalize()
{
	float length = Magnitude();

	x /= length;
	y /= length;
}

float2 float2::Normalize(float2 &value)
{
	float length = Magnitude(value);

	value.x /= length;
	value.y /= length;

	return value;
}

float2 float2::Normalized()
{
	return Normalize(*this);
}

void float2::Scale(float2 scale)
{
	x *= scale.x;
	y *= scale.y;
}

void float2::Set(float new_x, float new_y)
{
	x = new_x;
	y = new_y;
}

float2& float2::operator/=(const float2 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;

	return *this;
}

float2& float2::operator*=(const float2 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}

float2& float2::operator-=(const float2 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

float2 float2::operator-() const
{
	float2 value;

	value.x = -x;
	value.y = -y;

	return value;
}

float2& float2::operator+=(const float2 &rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

float2& float2::operator=(const float2 &rhs)
{
	x = rhs.x;
	y = rhs.y;

	return *this;
}

float2 operator+(const float2 &lhs, const float2 &rhs)
{
	float2 result = lhs;

	result += rhs;

	return result;
}

float2 operator-(const float2 &lhs, const float2 &rhs)
{
	float2 result = lhs;

	result -= rhs;

	return result;
}

float2 operator*(const float2 &lhs, const float2 &rhs)
{
	float2 result = lhs;

	result *= rhs;

	return result;
}

float2 operator/(const float2 &lhs, const float2 &rhs)
{
	float2 result = lhs;

	result /= rhs;

	return result;
}

std::ostream & operator<<(std::ostream &os, const float2 &value)
{
	os << "(" << value.x << ", " << value.y << ")";

	return os;
}

std::istream & operator >> (std::istream &is, float2 &value)
{
	is >> value.x >> value.y;

	return is;
}

bool operator==(const float2 &lhs, const float2 &rhs)
{
	bool result = false;

	if (lhs.x == rhs.x && lhs.y == rhs.y)
	{
		result = true;
	}

	return result;

}

bool operator!=(const float2 &lhs, const float2 &rhs)
{
	return !(lhs == rhs);
}

template<typename T>
float2& float2::operator/=(const T &rhs)
{
	x /= rhs;
	y /= rhs;

	return *this;
}

template<typename T>
float2& float2::operator*=(const T &rhs)
{
	x *= rhs;
	y *= rhs;

	return *this;
}

template<typename T>
float2 operator*(const float2 &lhs, const T rhs)
{
	float2 result = lhs;

	result *= rhs;

	return result;
}

template<typename T>
float2 operator*(const T lhs, const float2 &rhs)
{
	float2 result = rhs;

	result *= lhs;

	return result;
}

template<typename T>
float2 operator/(const float2 &lhs, const T rhs)
{
	float2 result = lhs;

	result /= rhs;

	return result;
}