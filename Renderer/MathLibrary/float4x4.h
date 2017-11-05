#pragma once
#include "float3.h"
#include "float4.h"

class float4x4
{
public:
    static const float4x4 ZERO;
    static const float4x4 IDENTITY;

    float4x4();
    float4x4(const float4x4& mtx44);
    float4x4(const float3& v1, const float3& v2, const float3& v3);
    float4x4(const float4& v1, const float4& v2, const float4& v3, const float4& v4);
    ~float4x4();

    void Zero();
    void Identity();

    float4x4 Translate(const float3& translate);
    float4x4 RotateX(float theta);
    float4x4 RotateY(float theta);
    float4x4 RotateZ(float theta);
    float4x4 Rotation(float yaw, float pitch, float roll);
    float4x4 Rotation(const float3& axis, float angle);
    float4x4 Rotation(const float3& axis, const float3& center, float angle);
    float4x4 Scale(const float3& scale);

    float4x4 Transpose();
    float4x4 Inverse();

    float4x4 Camera(const float3& eye, const float3& look, const float3& up, const float3& right);
    float4x4 LookAt(const float3& eye, const float3& destination, const float3& up);
    float4x4 Orthogonal(float width, float height, float z_near, float z_far);
    float4x4 Perspective(float width, float height, float z_near, float z_far);
    float4x4 PerspectiveFOV(float fov, float aspect, float z_near, float z_far);
    float4x4 PerspectiveMultiFOV(float fov_x, float fov_y, float z_near, float z_far);

#pragma region Overloaded Operators
    float4& operator[] (size_t n) { return matrix[n]; }
    const float4& operator[] (size_t n) const { return matrix[n]; }
    float4x4& operator=(const float4x4 &rhs);
    float4x4& operator+=(const float4x4 &rhs);
    float4x4& operator-=(const float4x4 &rhs);
    float4x4 operator-() const;
    float4x4& operator*=(const float4x4 &rhs);
    float4x4& operator/=(const float4x4 &rhs);
    float4x4& operator*=(const float &rhs);
    float4x4& operator/=(const float &rhs);

    friend bool operator==(const float4x4 &lhs, const float4x4 &rhs);
    friend std::ostream &operator<<(std::ostream &os, const float4x4 &value);
    friend std::istream &operator>>(std::istream &is, float4x4 &value);
#pragma endregion Overloaded Operators

    float4 matrix[4];
};

float4x4 operator+(const float4x4 &lhs, const float4x4 &rhs);
float4x4 operator-(const float4x4 &lhs, const float4x4 &rhs);
float4x4 operator-(const float4x4 &lhs, const float &rhs);
float4x4 operator*(const float4x4 &lhs, const float4x4 &rhs);
float4x4 operator/(const float4x4 &lhs, const float4x4 &rhs);
bool operator!=(const float4x4 &lhs, const float4x4 &rhs);

float4x4 operator*(const float4x4 &lhs, const float &rhs);
float4x4 operator*(const float &lhs, const float4x4 &rhs);
float4x4 operator/(const float4x4 &lhs, const float &rhs);

float4x4 operator*(const float4x4& lhs, const float3& rhs);
float4x4 operator*(const float3& lhs, const float4x4& rhs);
float4x4 operator/(const float4x4& lhs, const float3& rhs);
float4x4 operator/(const float3& lhs, const float4x4& rhs);
float4x4 operator*(const float4x4& lhs, const float4& rhs);
float4x4 operator*(const float4& lhs, const float4x4& rhs);
float4x4 operator/(const float4x4& lhs, const float4& rhs);
float4x4 operator/(const float4& lhs, const float4x4& rhs);