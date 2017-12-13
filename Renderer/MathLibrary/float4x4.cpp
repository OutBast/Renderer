#include "stdafx.h"
#include "float4x4.h"

#include <sstream>
#include <cmath>

using namespace std;

float4x4::float4x4()
{
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        m[i] = float4::zero;
    }
}

float4x4::float4x4(const four_as_column& fourAsColumn, float mColumn0Row0, float mColumn0Row1, float mColumn0Row2, float mColumn0Row3, float mColumn1Row0, float mColumn1Row1, float mColumn1Row2, float mColumn1Row3, float mColumn2Row0, float mColumn2Row1, float mColumn2Row2, float mColumn2Row3, float mColumn3Row0, float mColumn3Row1, float mColumn3Row2, float mColumn3Row3)
{
    m[0][0] = mColumn0Row0;
    m[0][1] = mColumn0Row1;
    m[0][2] = mColumn0Row2;
    m[0][3] = mColumn0Row3;

    m[1][0] = mColumn1Row0;
    m[1][1] = mColumn1Row1;
    m[1][2] = mColumn1Row2;
    m[1][3] = mColumn1Row3;

    m[2][0] = mColumn2Row0;
    m[2][1] = mColumn2Row1;
    m[2][2] = mColumn2Row2;
    m[2][3] = mColumn2Row3;

    m[3][0] = mColumn3Row0;
    m[3][1] = mColumn3Row1;
    m[3][2] = mColumn3Row2;
    m[3][3] = mColumn3Row3;
}

float4x4::float4x4(const four_as_row& fourAsRow, float mColumn0Row0, float mColumn1Row0, float mColumn2Row0, float mColumn3Row0, float mColumn0Row1, float mColumn1Row1, float mColumn2Row1, float mColumn3Row1, float mColumn0Row2, float mColumn1Row2, float mColumn2Row2, float mColumn3Row2, float mColumn0Row3, float mColumn1Row3, float mColumn2Row3, float mColumn3Row3)
    : float4x4(eachNextFourValuesRepresentsOneColumn, mColumn0Row0, mColumn0Row1, mColumn0Row2, mColumn0Row3, mColumn1Row0, mColumn1Row1, mColumn1Row2, mColumn1Row3, mColumn2Row0, mColumn2Row1, mColumn2Row2, mColumn2Row3, mColumn3Row0, mColumn3Row1, mColumn3Row2, mColumn3Row3)
{

}

float4x4::float4x4(const four_as_column& fourAsColumn, float values[])
{
    int index = 0;
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_ROWS; ++j)
        {
            m[i][j] = values[index++];
        }
    }
}

float4x4::float4x4(const four_as_row& fourAsRow, float values[])
{
    int index = 0;
    for (int i = 0; i < MATRIX_NUMBER_OF_ROWS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_COLUMNS; ++j)
        {
            m[j][i] = values[index++];
        }
    }
}

float4x4::float4x4(const four_as_column& fourAsColumn, const float4& column0, const float4& column1, const float4& column2, const float4& column3)
{
    m[0] = column0;
    m[1] = column1;
    m[2] = column2;
    m[3] = column3;
}

float4x4::float4x4(const four_as_row& fourAsRow, const float4& row0, const float4& row1, const float4& row2, const float4& row3)
{
    m[0] = float4(row0.x, row1.x, row2.x, row3.x);
    m[1] = float4(row0.y, row1.y, row2.y, row3.y);
    m[2] = float4(row0.z, row1.z, row2.z, row3.z);
    m[3] = float4(row0.w, row1.w, row2.w, row3.w);
}

const float4x4 float4x4::ZERO = float4x4(eachNextFourValuesRepresentsOneColumn,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f
);

const float4x4 float4x4::IDENTITY = float4x4(eachNextFourValuesRepresentsOneRow,
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

float4 float4x4::getColumn(int index) const
{
    return m[index];
}

float4 float4x4::getRow(int index) const
{
    return float4(m[0][index], m[1][index], m[2][index], m[3][index]);
}

float4x4 float4x4::clamped01() const
{
    float4x4 resultMatrix;
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_ROWS; ++j)
        {
            resultMatrix.m[i][j] = ClampSingle(m[i][j], 0.0f, 1.0f);
        }
    }
    return resultMatrix;
}

void float4x4::clamp01()
{
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_ROWS; ++j)
        {
            m[i][j] = ClampSingle(m[i][j], 0.0f, 1.0f);
        }
    }
}

float4x4 float4x4::operator+(const float4x4& rhs) const
{
    float4x4 matrix(*this);
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_ROWS; ++j)
        {
            matrix.m[i][j] += rhs.m[i][j];
        }
    }
    return matrix;
}

float4x4 float4x4::operator-(const float4x4& rhs) const
{
    float4x4 matrix(*this);
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_ROWS; ++j)
        {
            matrix.m[i][j] -= rhs.m[i][j];
        }
    }
    return matrix;
}

float4x4 float4x4::operator*(const float4x4& rhs) const
{
    float4x4 resultMatrix;
    for (int i = 0; i < MATRIX_NUMBER_OF_ROWS; ++i)
    {
        float4 currentOurMatrixRow = getRow(i);
        for (int j = 0; j < MATRIX_NUMBER_OF_COLUMNS; ++j)
        {
            resultMatrix.m[j][i] = float4::Dot(currentOurMatrixRow, rhs.m[j]);
        }
    }
    return resultMatrix;
}

float4x4 float4x4::operator*(float rhs) const
{
    float4x4 matrix(*this);
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_ROWS; ++j)
        {
            matrix.m[i][j] *= rhs;
        }
    }
    return matrix;
}

float4 float4x4::operator*(const float4& vector) const
{
    return float4
    (
        m[0][0] * vector.x + m[1][0] * vector.y + m[2][0] * vector.z + m[3][0] * vector.w,
        m[0][1] * vector.x + m[1][1] * vector.y + m[2][1] * vector.z + m[3][1] * vector.w,
        m[0][2] * vector.x + m[1][2] * vector.y + m[2][2] * vector.z + m[3][2] * vector.w,
        m[0][3] * vector.x + m[1][3] * vector.y + m[2][3] * vector.z + m[3][3] * vector.w
    );
}

float4 float4x4::operator*(const float3& vector) const
{
    return operator*(float4(vector));
}

float4x4& float4x4::operator+=(const float4x4& rhs)
{
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_ROWS; ++j)
        {
            m[i][j] += rhs.m[i][j];
        }
    }
    return *this;
}

float4x4& float4x4::operator-=(const float4x4& rhs)
{
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_ROWS; ++j)
        {
            m[i][j] -= rhs.m[i][j];
        }
    }
    return *this;
}

float4x4& float4x4::operator*=(const float4x4& rhs)
{
    *this = (*this) * rhs;
    return *this;
}

float4x4& float4x4::operator*=(float rhs)
{
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_ROWS; ++j)
        {
            m[i][j] *= rhs;
        }
    }
    return *this;
}

bool float4x4::operator==(const float4x4& second) const
{
    return false;
}

float4& float4x4::operator[](size_t index)
{
    return m[index];
}

const float4& float4x4::operator[](size_t index) const
{
    return m[index];
}

float4x4 float4x4::createScale(const float3& scale)
{
    return float4x4
    (
        eachNextFourValuesRepresentsOneRow,
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    );
}

float4x4 float4x4::createTranslation(const float3& translation)
{
    return float4x4
    (
        eachNextFourValuesRepresentsOneRow,
        1, 0, 0, translation.x,
        0, 1, 0, translation.y,
        0, 0, 1, translation.z,
        0, 0, 0, 1
    );
}

float4x4 float4x4::createRotationX(float angleInRadians)
{
    return float4x4
    (
        eachNextFourValuesRepresentsOneRow,
        1, 0, 0, 0,
        0, cos(angleInRadians), -sin(angleInRadians), 0,
        0, sin(angleInRadians), cos(angleInRadians), 0,
        0, 0, 0, 1
    );
}

float4x4 float4x4::createRotationY(float angleInRadians)
{
    return float4x4
    (
        eachNextFourValuesRepresentsOneRow,
        cos(angleInRadians), 0, sin(angleInRadians), 0,
        0, 1, 0, 0,
        -sin(angleInRadians), 0, cos(angleInRadians), 0,
        0, 0, 0, 1
    );
}

float4x4 float4x4::createRotationZ(float angleInRadians)
{
    return float4x4
    (
        eachNextFourValuesRepresentsOneRow,
        cos(angleInRadians), -sin(angleInRadians), 0, 0,
        sin(angleInRadians), cos(angleInRadians), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

float4x4 float4x4::createRotation(float angleInRadians, const float3& vector)
{
    float3 normalizedRotationVector = vector.Normalized();
    float x = normalizedRotationVector.x;
    float y = normalizedRotationVector.y;
    float z = normalizedRotationVector.z;
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float c = cos(angleInRadians);
    float s = sin(angleInRadians);
    float oneMinusC = 1.0F - c;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float xs = x * s;
    float ys = y * s;
    float zs = z * s;

    return float4x4
    (
        eachNextFourValuesRepresentsOneRow,
        (x2 * oneMinusC) + c, (xy * oneMinusC) - zs, (xz * oneMinusC) + ys, 0.0F,
        (xy * oneMinusC) + zs, (y2 * oneMinusC) + c, (yz * oneMinusC) - xs, 0.0F,
        (xz * oneMinusC) - ys, (yz * oneMinusC) + xs, (z2 * oneMinusC) + c, 0.0F,
        0.0F, 0.0F, 0.0F, 1.0F
    );
}

float4x4 float4x4::createLookAt(const float3& eye, const float3& target, const float3& upVector)
{
    // Compute the forward vector from target to eye
    // If switched to left-handed coordinate system, just revert
    // the order of eye and target and everything  else will be fine
    // (note that left will become right but code will remain the
    // same for computing it)
    float3 forward = eye - target;
    forward.Normalize();

    // Compute the left vector
    // In left-handed system this will become right vector
    // But there is no need for change in code (unless you
    // just want to change the name from left to right
    float3 left = float3::Cross(upVector, forward);
    left.Normalize();

    // Recompute the orthonormal up vector
    float3 up = float3::Cross(forward, left);

    return float4x4
    (
        eachNextFourValuesRepresentsOneRow,
        left.x, left.y, left.z, -float3::Dot(left, eye),
        up.x, up.y, up.z, -float3::Dot(up, eye),
        forward.x, forward.y, forward.z, -float3::Dot(forward, eye),
        0.0F, 0.0F, 0.0F, 1.0F
    );
}

float4x4 float4x4::createPerspective(float fovy, float aspect, float nearPlane, float farPlane)
{
    float angleInRadians = DegreesToRadians(fovy);
    float f = 1.0F / tan(angleInRadians * 0.5F);
    float nearPlaneMinusFarPlane = nearPlane - farPlane;

    return float4x4
    (
        eachNextFourValuesRepresentsOneRow,
        f / aspect, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (farPlane + nearPlane) / (nearPlaneMinusFarPlane), (2.0F * farPlane * nearPlane) / (nearPlaneMinusFarPlane),
        0, 0, -1.0F, 0
    );

}

float4x4 float4x4::createOrthographic(float left, float right, float top, float bottom, float nearPlane, float farPlane)
{
    float rightMinusLeft = right - left;
    float topMinusBottom = top - bottom;
    float farPlaneMinusNearPlane = farPlane - nearPlane;

    return float4x4
    (
        eachNextFourValuesRepresentsOneRow,
        2.0F / rightMinusLeft, 0, 0, -((right + left) / rightMinusLeft),
        0, 2.0F / topMinusBottom, 0, -((top + bottom) / topMinusBottom),
        0, 0, -2.0F / farPlaneMinusNearPlane, -((farPlane + nearPlane) / farPlaneMinusNearPlane),
        0, 0, 0, 1.0F
    );
}

float float4x4::getDeterminant(const float4x4& matrix)
{
    return
        matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][2] * matrix.m[0][3] - matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][2] * matrix.m[0][3] -
        matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[0][3] + matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][2] * matrix.m[0][3] +
        matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][2] * matrix.m[0][3] - matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] * matrix.m[0][3] -
        matrix.m[3][0] * matrix.m[2][1] * matrix.m[0][2] * matrix.m[1][3] + matrix.m[2][0] * matrix.m[3][1] * matrix.m[0][2] * matrix.m[1][3] +
        matrix.m[3][0] * matrix.m[0][1] * matrix.m[2][2] * matrix.m[1][3] - matrix.m[0][0] * matrix.m[3][1] * matrix.m[2][2] * matrix.m[1][3] -
        matrix.m[2][0] * matrix.m[0][1] * matrix.m[3][2] * matrix.m[1][3] + matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2] * matrix.m[1][3] +
        matrix.m[3][0] * matrix.m[1][1] * matrix.m[0][2] * matrix.m[2][3] - matrix.m[1][0] * matrix.m[3][1] * matrix.m[0][2] * matrix.m[2][3] -
        matrix.m[3][0] * matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] + matrix.m[0][0] * matrix.m[3][1] * matrix.m[1][2] * matrix.m[2][3] +
        matrix.m[1][0] * matrix.m[0][1] * matrix.m[3][2] * matrix.m[2][3] - matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2] * matrix.m[2][3] -
        matrix.m[2][0] * matrix.m[1][1] * matrix.m[0][2] * matrix.m[3][3] + matrix.m[1][0] * matrix.m[2][1] * matrix.m[0][2] * matrix.m[3][3] +
        matrix.m[2][0] * matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3] - matrix.m[0][0] * matrix.m[2][1] * matrix.m[1][2] * matrix.m[3][3] -
        matrix.m[1][0] * matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3];
}

float4x4 float4x4::inverse(const float4x4& matrix)
{
    float4x4 newMatrix;
    float s0 = matrix.m[0][0] * matrix.m[1][1] - matrix.m[1][0] * matrix.m[0][1];
    float s1 = matrix.m[0][0] * matrix.m[1][2] - matrix.m[1][0] * matrix.m[0][2];
    float s2 = matrix.m[0][0] * matrix.m[1][3] - matrix.m[1][0] * matrix.m[0][3];
    float s3 = matrix.m[0][1] * matrix.m[1][2] - matrix.m[1][1] * matrix.m[0][2];
    float s4 = matrix.m[0][1] * matrix.m[1][3] - matrix.m[1][1] * matrix.m[0][3];
    float s5 = matrix.m[0][2] * matrix.m[1][3] - matrix.m[1][2] * matrix.m[0][3];

    float c5 = matrix.m[2][2] * matrix.m[3][3] - matrix.m[3][2] * matrix.m[2][3];
    float c4 = matrix.m[2][1] * matrix.m[3][3] - matrix.m[3][1] * matrix.m[2][3];
    float c3 = matrix.m[2][1] * matrix.m[3][2] - matrix.m[3][1] * matrix.m[2][2];
    float c2 = matrix.m[2][0] * matrix.m[3][3] - matrix.m[3][0] * matrix.m[2][3];
    float c1 = matrix.m[2][0] * matrix.m[3][2] - matrix.m[3][0] * matrix.m[2][2];
    float c0 = matrix.m[2][0] * matrix.m[3][1] - matrix.m[3][0] * matrix.m[2][1];

    float det = (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

    float invdet = 1.0F / det;

    newMatrix.m[0][0] = (matrix.m[1][1] * c5 - matrix.m[1][2] * c4 + matrix.m[1][3] * c3) * invdet;
    newMatrix.m[0][1] = (-matrix.m[0][1] * c5 + matrix.m[0][2] * c4 - matrix.m[0][3] * c3) * invdet;
    newMatrix.m[0][2] = (matrix.m[3][1] * s5 - matrix.m[3][2] * s4 + matrix.m[3][3] * s3) * invdet;
    newMatrix.m[0][3] = (-matrix.m[2][1] * s5 + matrix.m[2][2] * s4 - matrix.m[2][3] * s3) * invdet;

    newMatrix.m[1][0] = (-matrix.m[1][0] * c5 + matrix.m[1][2] * c2 - matrix.m[1][3] * c1) * invdet;
    newMatrix.m[1][1] = (matrix.m[0][0] * c5 - matrix.m[0][2] * c2 + matrix.m[0][3] * c1) * invdet;
    newMatrix.m[1][2] = (-matrix.m[3][0] * s5 + matrix.m[3][2] * s2 - matrix.m[3][3] * s1) * invdet;
    newMatrix.m[1][3] = (matrix.m[2][0] * s5 - matrix.m[2][2] * s2 + matrix.m[2][3] * s1) * invdet;

    newMatrix.m[2][0] = (matrix.m[1][0] * c4 - matrix.m[1][1] * c2 + matrix.m[1][3] * c0) * invdet;
    newMatrix.m[2][1] = (-matrix.m[0][0] * c4 + matrix.m[0][1] * c2 - matrix.m[0][3] * c0) * invdet;
    newMatrix.m[2][2] = (matrix.m[3][0] * s4 - matrix.m[3][1] * s2 + matrix.m[3][3] * s0) * invdet;
    newMatrix.m[2][3] = (-matrix.m[2][0] * s4 + matrix.m[2][1] * s2 - matrix.m[2][3] * s0) * invdet;

    newMatrix.m[3][0] = (-matrix.m[1][0] * c3 + matrix.m[1][1] * c1 - matrix.m[1][2] * c0) * invdet;
    newMatrix.m[3][1] = (matrix.m[0][0] * c3 - matrix.m[0][1] * c1 + matrix.m[0][2] * c0) * invdet;
    newMatrix.m[3][2] = (-matrix.m[3][0] * s3 + matrix.m[3][1] * s1 - matrix.m[3][2] * s0) * invdet;
    newMatrix.m[3][3] = (matrix.m[2][0] * s3 - matrix.m[2][1] * s1 + matrix.m[2][2] * s0) * invdet;

    return newMatrix;
}

float4x4 float4x4::transpose(const float4x4& matrix)
{
    float4x4 newMatrix;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            newMatrix.m[i][j] = matrix.m[j][i];
        }
    }
    return newMatrix;
}

float4x4 float4x4::clamp(const float4x4& matrix, float minValue, float maxValue)
{
    float4x4 resultMatrix;
    for (int i = 0; i < MATRIX_NUMBER_OF_COLUMNS; ++i)
    {
        for (int j = 0; j < MATRIX_NUMBER_OF_ROWS; ++j)
        {
            resultMatrix.m[i][j] = ClampSingle(matrix.m[i][j], minValue, maxValue);
        }
    }
    return resultMatrix;
}

float4x4::~float4x4()
{

}
