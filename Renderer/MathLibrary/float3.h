#pragma once

class float3
{
public:
#pragma region Static & Const
	const float epsilon = 1E-05F;
	static float3 back;
	static float3 down;
	static float3 forward;
	static float3 left;
	static float3 right;
	static float3 up;
	static float3 zero;
	static float3 one;

	static float Angle(const float3 &from, const float3 &to);
	static float3 Cross(const float3 &a, const float3 &b);
	static float Distance(const float3 &from, const float3 &to);
	static float Dot(const float3 &a, const float3 &b);
	static float Magnitude(const float3 &value);
	static float SqrMagnitude(const float3 &value);
	static float3 Normalize(const float3 &value);
	static float3 Reflect(const float3 &direction, const float3 &normal);
	static float3 Refract(float inFactor, float outFactor, const float3& direction, const float3& normal);
	static float3 Reverse(const float3 &value);
#pragma endregion Static & Const

#pragma region Member Functions & Constructors
	float3();
	float3(float x, float y);
	float3(float x, float y, float z);
	float3(int x, int y, int z);
	float3(const float3 &value);
	~float3();

	float Angle(float3 &rhs);
    float Distance(float3 &rhs);
    float Magnitude();
	float Magnitude() const;
	float SqrMagnitude();
	float Dot(float3 &rhs);
	float3 Cross(float3 &rhs);
	void Normalize();
	float3 Normalized();
	float3 Reflect(float3 &normal);
	void Reverse();
	void Scale(float3 scale);
	void Set(float new_x, float new_y, float new_z);
#pragma endregion Member Functions & Constructors

#pragma region Overloaded Operators
	float& operator[] (size_t n) { return v[n]; }
	const float& operator[] (size_t n) const { return v[n]; }
	float3& operator=(const float3 &rhs);
	float3& operator+=(const float3 &rhs);
	float3& operator-=(const float3 &rhs);
	float3 operator-() const;
	float3& operator*=(const float3 &rhs);
	float3& operator/=(const float3 &rhs);
	float3& operator*=(const float &rhs);
	float3& operator/=(const float &rhs);

	friend bool operator==(const float3 &lhs, const float3 &rhs);
	friend std::ostream &operator<<(std::ostream &os, const float3 &value);
	friend std::istream &operator >> (std::istream &is, float3 &value);
#pragma endregion Overloaded Operators

#pragma region Getters & Setters
	float X() const { return x; }
	void X(float val) { x = val; }
	float Y() const { return y; }
	void Y(float val) { y = val; }
	float Z() const { return z; }
	void Z(float val) { z = val; }
	float R() const { return r; }
	void R(float val) { r = val; }
	float G() const { return g; }
	void G(float val) { g = val; }
	float B() const { return b; }
	void B(float val) { b = val; }
	float V(int index) const { if(index >= 0 && index < 3) return v[index]; }
	void V(float val, int index) { if (index >= 0 && index < 3) v[index] = val; }
#pragma endregion Getters & Setters
private:
	union
	{
		struct
		{
			float x, y, z;
		};

		struct
		{
			float r, g, b;
		};

		float v[3];
	};
};

float3 operator+(const float3 &lhs, const float3 &rhs);
float3 operator-(const float3 &lhs, const float3 &rhs);
float3 operator-(const float3 &lhs, const float &rhs);
float3 operator*(const float3 &lhs, const float3 &rhs);
float3 operator/(const float3 &lhs, const float3 &rhs);
bool operator!=(const float3 &lhs, const float3 &rhs);
float3 operator*(const float3 &lhs, const float &rhs);
float3 operator*(const float &lhs, const float3 &rhs);
float3 operator/(const float3 &lhs, const float &rhs);