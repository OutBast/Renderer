#include "stdafx.h"
#include "float4x4.h"

const float4x4 float4x4::ZERO = float4x4(
                                            float4(0.0f, 0.0f, 0.0f, 0.0f),
                                            float4(0.0f, 0.0f, 0.0f, 0.0f),
                                            float4(0.0f, 0.0f, 0.0f, 0.0f),
                                            float4(0.0f, 0.0f, 0.0f, 0.0f)
                                        );

const float4x4 float4x4::IDENTITY = float4x4(
                                                float4(1.0f, 0.0f, 0.0f, 0.0f),
                                                float4(0.0f, 1.0f, 0.0f, 0.0f),
                                                float4(0.0f, 0.0f, 1.0f, 0.0f),
                                                float4(0.0f, 0.0f, 0.0f, 1.0f)
                                            );

float4x4::float4x4()
{
    Zero();
}

float4x4::float4x4(const float4& v1, const float4& v2, const float4& v3, const float4& v4)
{
    matrix[0][0] = v1.X();
    matrix[0][1] = v1.Y();
    matrix[0][2] = v1.Z();
    matrix[0][3] = v1.W();

    matrix[1][0] = v2.X();
    matrix[1][1] = v2.Y();
    matrix[1][2] = v2.Z();
    matrix[1][3] = v2.W();

    matrix[2][0] = v3.X();
    matrix[2][1] = v3.Y();
    matrix[2][2] = v3.Z();
    matrix[2][3] = v3.W();

    matrix[3][0] = v4.X();
    matrix[3][1] = v4.Y();
    matrix[3][2] = v4.Z();
    matrix[3][3] = v4.W();
}

float4x4::float4x4(const float3& v1, const float3& v2, const float3& v3)
{
    matrix[0][0] = v1.X();
    matrix[0][1] = v1.Y();
    matrix[0][2] = v1.Z();
    matrix[0][3] = 0.0f;

    matrix[1][0] = v2.X();
    matrix[1][1] = v2.Y();
    matrix[1][2] = v2.Z();
    matrix[1][3] = 0.0f;

    matrix[2][0] = v3.X();
    matrix[2][1] = v3.Y();
    matrix[2][2] = v3.Z();
    matrix[2][3] = 0.0f;

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
}

float4x4::float4x4(const float4x4& mtx44)
{
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            matrix[i][j] = mtx44[i][j];
        }
    }
}

float4x4::~float4x4()
{
}

void float4x4::Zero()
{
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            matrix[i][j] = 0.0f;
        }
    }
}

void float4x4::Identity()
{
    matrix[0] = float4(1.0f, 0.0f, 0.0f, 0.0f);
    matrix[1] = float4(0.0f, 1.0f, 0.0f, 0.0f);
    matrix[2] = float4(0.0f, 0.0f, 1.0f, 0.0f);
    matrix[3] = float4(0.0f, 0.0f, 0.0f, 1.0f);
}

float4x4 float4x4::Translate(const float3& translate)
{
    float4x4 mtx44;

    mtx44[0][0] = 1.0f;
    mtx44[1][0] = 0.0f;
    mtx44[2][0] = 0.0f;
    mtx44[3][0] = translate.X();

    mtx44[0][1] = 0.0f;
    mtx44[1][1] = 1.0f;
    mtx44[2][1] = 0.0f;
    mtx44[3][1] = translate.Y();

    mtx44[0][2] = 0.0f;
    mtx44[1][2] = 0.0f;
    mtx44[2][2] = 1.0f;
    mtx44[3][2] = translate.Z();

    mtx44[0][3] = 0.0f;
    mtx44[1][3] = 0.0f;
    mtx44[2][3] = 0.0f;
    mtx44[3][3] = 1.0f;

    return mtx44;
}

float4x4 float4x4::RotateX(float theta)
{
    float cos_t = cosf(theta);
    float sin_t = sinf(theta);

    float4x4 mtx44 = float4x4::IDENTITY;

    mtx44[1][1] = cos_t;
    mtx44[1][2] = sin_t;
    mtx44[2][1] = -sin_t;
    mtx44[2][2] = cos_t;

    return mtx44;
}

float4x4 float4x4::RotateY(float theta)
{
    float cos_t = cosf(theta);
    float sin_t = sinf(theta);

    float4x4 mtx44 = float4x4::IDENTITY;

    mtx44[0][0] = cos_t;
    mtx44[0][2] = sin_t;
    mtx44[2][0] = -sin_t;
    mtx44[2][2] = cos_t;

    return mtx44;
}

float4x4 float4x4::RotateZ(float theta)
{
    float cos_t = cosf(theta);
    float sin_t = sinf(theta);

    float4x4 mtx44 = float4x4::IDENTITY;

    mtx44[0][0] = cos_t;
    mtx44[0][1] = sin_t;
    mtx44[1][0] = -sin_t;
    mtx44[1][1] = cos_t;

    return mtx44;
}

float4x4 float4x4::Rotation(float yaw, float pitch, float roll)
{
    return RotateY(yaw) * RotateX(pitch) * RotateZ(roll);
}

float4x4 float4x4::Rotation(const float3& axis, float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - c;

    float3 normalized_axis = float3::Normalize(axis);
    float x = normalized_axis.X();
    float y = normalized_axis.Y();
    float z = normalized_axis.Z();

    float4x4 mtx44;

    mtx44[0][0] = 1.0f + t *(sqr(x) - 1.0f);
    mtx44[0][1] = z * s + t * x * y;
    mtx44[0][2] = -y * s + t * x * z;
    mtx44[0][3] = 0.0f;

    mtx44[1][0] = -z * s + t * x * y;
    mtx44[1][1] = 1.0f + t*(sqr(y) - 1.0f);
    mtx44[1][2] = x * s + t * y * z;
    mtx44[1][3] = 0.0f;

    mtx44[2][0] = y * s + t * x * z;
    mtx44[2][1] = -x * s + t * y * z;
    mtx44[2][2] = 1.0f + t*(z*z - 1.0f);
    mtx44[2][3] = 0.0f;

    mtx44[3][0] = 0.0f;
    mtx44[3][1] = 0.0f;
    mtx44[3][2] = 0.0f;
    mtx44[3][3] = 1.0f;

    return mtx44;
}

float4x4 float4x4::Rotation(const float3& axis, const float3& center, float angle)
{
    return Translate(-center) * Rotation(axis, angle) * Translate(center);
}

float4x4 float4x4::Scale(const float3& scale)
{
    float4x4 mtx44;

    mtx44[0][0] = scale.X();
    mtx44[1][0] = 0.0f;
    mtx44[2][0] = 0.0f;
    mtx44[3][0] = 0.0f;

    mtx44[0][1] = 0.0f;
    mtx44[1][1] = scale.Y();
    mtx44[2][1] = 0.0f;
    mtx44[3][1] = 0.0f;

    mtx44[0][2] = 0.0f;
    mtx44[1][2] = 0.0f;
    mtx44[2][2] = scale.Z();
    mtx44[3][2] = 0.0f;

    mtx44[0][3] = 0.0f;
    mtx44[1][3] = 0.0f;
    mtx44[2][3] = 0.0f;
    mtx44[3][3] = 1.0f;

    return mtx44;
}

float4x4 float4x4::Transpose()
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[j][i] = matrix[i][j];
        }
    }

    return mtx44;
}

float4x4 float4x4::Inverse()
{
    //
    // Inversion by Cramer's rule.  Code taken from an Intel publication
    //
    double Result[4][4];
    double tmp[12]; /* temp array for pairs */
    double src[16]; /* array of transpose source matrix */
    double det; /* determinant */
                /* transpose matrix */
    for (uint i = 0; i < 4; i++)
    {
        src[i + 0] = (*this)[i][0];
        src[i + 4] = (*this)[i][1];
        src[i + 8] = (*this)[i][2];
        src[i + 12] = (*this)[i][3];
    }
    /* calculate pairs for first 8 elements (cofactors) */
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];
    /* calculate first 8 elements (cofactors) */
    Result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
    Result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
    Result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
    Result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
    Result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
    Result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
    Result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
    Result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
    Result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
    Result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
    Result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
    Result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
    Result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
    Result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
    Result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
    Result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
    /* calculate pairs for second 8 elements (cofactors) */
    tmp[0] = src[2] * src[7];
    tmp[1] = src[3] * src[6];
    tmp[2] = src[1] * src[7];
    tmp[3] = src[3] * src[5];
    tmp[4] = src[1] * src[6];
    tmp[5] = src[2] * src[5];

    tmp[6] = src[0] * src[7];
    tmp[7] = src[3] * src[4];
    tmp[8] = src[0] * src[6];
    tmp[9] = src[2] * src[4];
    tmp[10] = src[0] * src[5];
    tmp[11] = src[1] * src[4];
    /* calculate second 8 elements (cofactors) */
    Result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
    Result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
    Result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
    Result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
    Result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
    Result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
    Result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
    Result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
    Result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
    Result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
    Result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
    Result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
    Result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
    Result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
    Result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
    Result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
    /* calculate determinant */
    det = src[0] * Result[0][0] + src[1] * Result[0][1] + src[2] * Result[0][2] + src[3] * Result[0][3];
    /* calculate matrix inverse */
    det = 1.0f / det;

    float4x4 FloatResult;
    for (uint i = 0; i < 4; i++)
    {
        for (uint j = 0; j < 4; j++)
        {
            FloatResult[i][j] = float(Result[i][j] * det);
        }
    }
    return FloatResult;
}

float4x4 float4x4::Camera(const float3& eye, const float3& look, const float3& up, const float3& right)
{
    //
    // Verify everything is normalized
    //
    float3 Look = float3::Normalize(look);
    float3 Up = float3::Normalize(up);
    float3 Right = float3::Normalize(right);

    float4x4 mtx44;
    mtx44[0][0] = Right.X();
    mtx44[1][0] = Right.Y();
    mtx44[2][0] = Right.Z();
    mtx44[3][0] = -float3::Dot(Right, eye);

    mtx44[0][1] = Up.X();
    mtx44[1][1] = Up.Y();
    mtx44[2][1] = Up.Z();
    mtx44[3][1] = -float3::Dot(Up, eye);

    mtx44[0][2] = Look.X();
    mtx44[1][2] = Look.Y();
    mtx44[2][2] = Look.Z();
    mtx44[3][2] = -float3::Dot(Look, eye);

    mtx44[0][3] = 0.0f;
    mtx44[1][3] = 0.0f;
    mtx44[2][3] = 0.0f;
    mtx44[3][3] = 1.0f;
    return mtx44;
}

float4x4 float4x4::LookAt(const float3& eye, const float3& destination, const float3& up)
{
    float3 XAxis, YAxis, ZAxis;
    ZAxis = float3::Normalize(eye - destination);
    XAxis = float3::Normalize(float3::Cross(up, ZAxis));
    YAxis = float3::Normalize(float3::Cross(ZAxis, XAxis));

    float4x4 mtx44;
    mtx44[0][0] = XAxis.X();
    mtx44[1][0] = XAxis.Y();
    mtx44[2][0] = XAxis.Z();
    mtx44[3][0] = -float3::Dot(XAxis, eye);

    mtx44[0][1] = YAxis.X();
    mtx44[1][1] = YAxis.Y();
    mtx44[2][1] = YAxis.Z();
    mtx44[3][1] = -float3::Dot(YAxis, eye);

    mtx44[0][2] = ZAxis.X();
    mtx44[1][2] = ZAxis.Y();
    mtx44[2][2] = ZAxis.Z();
    mtx44[3][2] = -float3::Dot(ZAxis, eye);

    mtx44[0][3] = 0.0f;
    mtx44[1][3] = 0.0f;
    mtx44[2][3] = 0.0f;
    mtx44[3][3] = 1.0f;
    return mtx44;
}

float4x4 float4x4::Orthogonal(float width, float height, float z_near, float z_far)
{
    float4x4 mtx44;
    mtx44[0][0] = 2.0f / width;
    mtx44[1][0] = 0.0f;
    mtx44[2][0] = 0.0f;
    mtx44[3][0] = 0.0f;

    mtx44[0][1] = 0.0f;
    mtx44[1][1] = 2.0f / height;
    mtx44[2][1] = 0.0f;
    mtx44[3][1] = 0.0f;

    mtx44[0][2] = 0.0f;
    mtx44[1][2] = 0.0f;
    mtx44[2][2] = 1.0f / (z_near - z_far);
    mtx44[3][2] = z_near / (z_near - z_far);

    mtx44[0][3] = 0.0f;
    mtx44[1][3] = 0.0f;
    mtx44[2][3] = 0.0f;
    mtx44[3][3] = 1.0f;
    return mtx44;
}

float4x4 float4x4::Perspective(float width, float height, float z_near, float z_far)
{
    float4x4 mtx44;
    mtx44[0][0] = 2.0f * z_near / width;
    mtx44[1][0] = 0.0f;
    mtx44[2][0] = 0.0f;
    mtx44[3][0] = 0.0f;

    mtx44[0][1] = 0.0f;
    mtx44[1][1] = 2.0f * z_near / height;
    mtx44[2][1] = 0.0f;
    mtx44[3][1] = 0.0f;

    mtx44[0][2] = 0.0f;
    mtx44[1][2] = 0.0f;
    mtx44[2][2] = z_far / (z_near - z_far);
    mtx44[3][2] = z_far * z_near / (z_near - z_far);

    mtx44[0][3] = 0.0f;
    mtx44[1][3] = 0.0f;
    mtx44[2][3] = -1.0f;
    mtx44[3][3] = 0.0f;
    return mtx44;
}

float4x4 float4x4::PerspectiveFOV(float fov, float aspect, float z_near, float z_far)
{
    float Width = 1.0f / tanf(fov / 2.0f), Height = aspect / tanf(fov / 2.0f);

    float4x4 mtx44;
    mtx44[0][0] = Width;
    mtx44[1][0] = 0.0f;
    mtx44[2][0] = 0.0f;
    mtx44[3][0] = 0.0f;

    mtx44[0][1] = 0.0f;
    mtx44[1][1] = Height;
    mtx44[2][1] = 0.0f;
    mtx44[3][1] = 0.0f;

    mtx44[0][2] = 0.0f;
    mtx44[1][2] = 0.0f;
    mtx44[2][2] = z_far / (z_near - z_far);
    mtx44[3][2] = z_far * z_near / (z_near - z_far);

    mtx44[0][3] = 0.0f;
    mtx44[1][3] = 0.0f;
    mtx44[2][3] = -1.0f;
    mtx44[3][3] = 0.0f;
    return mtx44;
}

float4x4 float4x4::PerspectiveMultiFOV(float fov_x, float fov_y, float z_near, float z_far)
{
    float Width = 1.0f / tanf(fov_x / 2.0f), Height = 1.0f / tanf(fov_y / 2.0f);

    float4x4 mtx44;
    mtx44[0][0] = Width;
    mtx44[1][0] = 0.0f;
    mtx44[2][0] = 0.0f;
    mtx44[3][0] = 0.0f;

    mtx44[0][1] = 0.0f;
    mtx44[1][1] = Height;
    mtx44[2][1] = 0.0f;
    mtx44[3][1] = 0.0f;

    mtx44[0][2] = 0.0f;
    mtx44[1][2] = 0.0f;
    mtx44[2][2] = z_far / (z_near - z_far);
    mtx44[3][2] = z_far * z_near / (z_near - z_far);

    mtx44[0][3] = 0.0f;
    mtx44[1][3] = 0.0f;
    mtx44[2][3] = -1.0f;
    mtx44[3][3] = 0.0f;
    return mtx44;
}

float4x4& float4x4::operator-=(const float4x4 &rhs)
{
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            matrix[i][j] -= rhs[i][j];
        }
    }
}

float4x4 float4x4::operator-() const
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = -matrix[i][j];
        }
    }

    return mtx44;
}

float4x4& float4x4::operator/=(const float &rhs)
{
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            matrix[i][j] /= rhs;
        }
    }

    return *this;
}

float4x4& float4x4::operator*=(const float &rhs)
{
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            matrix[i][j] *= rhs;
        }
    }

    return *this;
}

float4x4& float4x4::operator/=(const float4x4 &rhs)
{
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            matrix[i][j] /= rhs[i][j];
        }
    }

    return *this;
}

float4x4& float4x4::operator*=(const float4x4 &rhs)
{
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            matrix[i][j] *= rhs[i][j];
        }
    }

    return *this;
}

float4x4& float4x4::operator+=(const float4x4 &rhs)
{
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            matrix[i][j] += rhs[i][j];
        }
    }

    return *this;
}

float4x4& float4x4::operator=(const float4x4 &rhs)
{
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            matrix[i][j] = rhs[i][j];
        }
    }

    return *this;
}

float4x4 operator+(const float4x4 &lhs, const float4x4 &rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] + rhs[i][j];
        }
    }

    return mtx44;
}

float4x4 operator-(const float4x4 &lhs, const float4x4 &rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] - rhs[i][j];
        }
    }

    return mtx44;
}

float4x4 operator-(const float4x4 &lhs, const float &rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] - rhs;
        }
    }

    return mtx44;
}

float4x4 operator*(const float4x4 &lhs, const float4x4 &rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] * rhs[i][j];
        }
    }

    return mtx44;
}

float4x4 operator*(const float4x4 &lhs, const float &rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] * rhs;
        }
    }

    return mtx44;
}

float4x4 operator*(const float &lhs, const float4x4 &rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs * rhs[i][j];
        }
    }

    return mtx44;
}

float4x4 operator*(const float4x4& lhs, const float3& rhs)
{
    float4x4 mtx44;
    float4 tmp = float4(rhs);

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] * tmp[j];
        }
    }

    return mtx44;
}

float4x4 operator*(const float4x4& lhs, const float4& rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] * rhs[j];
        }
    }

    return mtx44;
}

float4x4 operator*(const float3& lhs, const float4x4& rhs)
{
    float4x4 mtx44;
    float4 tmp = float4(lhs);

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = rhs[i][j] * tmp[j];
        }
    }

    return mtx44;
}

float4x4 operator*(const float4& lhs, const float4x4& rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = rhs[i][j] * lhs[j];
        }
    }

    return mtx44;
}

float4x4 operator/(const float4x4 &lhs, const float4x4 &rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] / rhs[i][j];
        }
    }

    return mtx44;
}

float4x4 operator/(const float4x4 &lhs, const float &rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] / rhs;
        }
    }

    return mtx44;
}

float4x4 operator/(const float4x4& lhs, const float3& rhs)
{
    float4x4 mtx44;
    float4 tmp = float4(rhs);

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] / tmp[j];
        }
    }

    return mtx44;
}

float4x4 operator/(const float4x4& lhs, const float4& rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = lhs[i][j] / rhs[j];
        }
    }

    return mtx44;
}

float4x4 operator/(const float3& lhs, const float4x4& rhs)
{
    float4x4 mtx44;
    float4 tmp = float4(lhs);

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = rhs[i][j] / tmp[j];
        }
    }

    return mtx44;
}

float4x4 operator/(const float4& lhs, const float4x4& rhs)
{
    float4x4 mtx44;

    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            mtx44[i][j] = rhs[i][j] / lhs[j];
        }
    }

    return mtx44;
}

bool operator!=(const float4x4 &lhs, const float4x4 &rhs)
{
    if (lhs == rhs)
    {
        return false;
    }

    return true;
}

bool operator==(const float4x4 &lhs, const float4x4 &rhs)
{
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            if (lhs[i][j] != rhs[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

std::ostream &operator<<(std::ostream &os, const float4x4 &value)
{
    for (uint i = 0; i < 4; ++i)
    {
        os << "[ " << value[i][0] << ", " << value[i][1] << ", " << value[i][2] << ", " << value[i][3] << " ]" << endl;
    }

    return os;
}

std::istream &operator>>(std::istream &is, float4x4 &value)
{

}