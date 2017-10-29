#pragma once

class float2
{
public:
#pragma region Static & Const
	const float epsilon = 1E-05F;
	static float2 down;
	static float2 left;
	static float2 right;
	static float2 up;
	static float2 zero;
	static float2 one;

	static double Angle(float2 &from, float2 &to);
	static float Distance(float2 &from, float2 &to);
	static float Dot(float2 &a, float2 &b);
	static float Magnitude(float2 &value);
	static float SqrMagnitude(float2 &value);
	static float2 Normalize(float2 &value);
#pragma endregion Static & Const

#pragma region Member Functions & Constructors
	float2();
	float2(float x, float y);
	float2(const float2 &value);
	~float2();

	double Angle(float2 &rhs);
	float Distance(float2 &rhs);
	float Magnitude();
	float SqrMagnitude();
	float Dot(float2 &rhs);
	void Normalize();
	float2 Normalized();
	void Scale(float2 scale);
	void Set(float new_x, float new_y);
#pragma endregion Member Functions & Constructors

#pragma region Overloaded Operators
	float& operator[] (size_t n) { return v[n]; }
	const float& operator[] (size_t n) const { return v[n]; }
	float2& operator=(const float2 &rhs);
	float2& operator+=(const float2 &rhs);
	float2& operator-=(const float2 &rhs);
	float2 operator-() const;
	float2& operator*=(const float2 &rhs);
	float2& operator/=(const float2 &rhs);
	template<typename T>
	float2& operator*=(const T &rhs);
	template<typename T>
	float2& operator/=(const T &rhs);

	friend bool operator==(const float2 &lhs, const float2 &rhs);
	friend std::ostream &operator<<(std::ostream &os, const float2 &value);
	friend std::istream &operator >> (std::istream &is, float2 &value);
	friend float2 operator+(const float2 &lhs, const float2 &rhs);
	friend float2 operator-(const float2 &lhs, const float2 &rhs);
	friend float2 operator*(const float2 &lhs, const float2 &rhs);
	friend float2 operator/(const float2 &lhs, const float2 &rhs);
	friend bool operator!=(const float2 &lhs, const float2 &rhs);
	template<typename T>
	friend float2 operator*(const float2 &lhs, const T rhs);
	template<typename T>
	friend float2 operator*(const T lhs, const float2 &rhs);
	template<typename T>
	friend float2 operator/(const float2 &lhs, const T rhs);
#pragma endregion Overloaded Operators

#pragma region Getters & Setters
	float X() const { return x; }
	void X(float val) { x = val; }
	float Y() const { return y; }
	void Y(float val) { y = val; }
#pragma endregion Getters & Setters
private:
	union
	{
		struct
		{
			float x, y;
		};
		
		float v[2];
	};
};