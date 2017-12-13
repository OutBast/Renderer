#pragma once

#include "float3.h"
#include "float4.h"


#define MATRIX_SIZE 16

/**
Also single row size
**/
#define MATRIX_NUMBER_OF_COLUMNS 4

/**
Also single column size
**/
#define MATRIX_NUMBER_OF_ROWS 4

struct four_as_column
{
    four_as_column(const four_as_column& second) = delete;
};
struct four_as_row
{
    four_as_row(const four_as_row& second) = delete;
};

/**
Consist of array of float4's.
A float4 IS A COLUMN!
So we use matrix[COLUMN_INDEX][ROW_INDEX]
**/
struct float4x4
{
private:

    /**
    m[COLUMN_INDEX][ROW_INDEX]
    **/
    float4 m[MATRIX_NUMBER_OF_COLUMNS];

public:

    static constexpr four_as_column eachNextFourValuesRepresentsOneColumn{};
    static constexpr four_as_row eachNextFourValuesRepresentsOneRow{};

    float4x4();
    float4x4(const four_as_column& fourAsColumn, float mColumn0Row0, float mColumn0Row1, float mColumn0Row2, float mColumn0Row3, float mColumn1Row0, float mColumn1Row1, float mColumn1Row2, float mColumn1Row3, float mColumn2Row0, float mColumn2Row1, float mColumn2Row2, float mColumn2Row3, float mColumn3Row0, float mColumn3Row1, float mColumn3Row2, float mColumn3Row3);
    float4x4(const four_as_row& fourAsRow, float mColumn0Row0, float mColumn1Row0, float mColumn2Row0, float mColumn3Row0, float mColumn0Row1, float mColumn1Row1, float mColumn2Row1, float mColumn3Row1, float mColumn0Row2, float mColumn1Row2, float mColumn2Row2, float mColumn3Row2, float mColumn0Row3, float mColumn1Row3, float mColumn2Row3, float mColumn3Row3);
    float4x4(const four_as_column& fourAsColumn, float values[]);
    float4x4(const four_as_row& fourAsRow, float values[]);
    float4x4(const four_as_column& fourAsColumn, const float4& column0, const float4& column1, const float4& column2, const float4& column3);
    float4x4(const four_as_row& fourAsRow, const float4& row0, const float4& row1, const float4& row2, const float4& row3);

    static const float4x4 ZERO;
    static const float4x4 IDENTITY;

    float4 getColumn(int index) const;
    float4 getRow(int index) const;

    float4x4 clamped01() const;
    void clamp01();
    
    float4x4 operator+(const float4x4& rhs) const;
    float4x4 operator-(const float4x4& rhs) const;
    float4x4 operator*(const float4x4& rhs) const;
    float4x4 operator*(float rhs) const;
    float4 operator*(const float4& vector) const;
    float4 operator*(const float3& vector) const;
    float4x4& operator+=(const float4x4& rhs);
    float4x4& operator-=(const float4x4& rhs);
    float4x4& operator*=(const float4x4& rhs);
    float4x4& operator*=(float rhs);
    bool operator==(const float4x4& second) const;

    //friend float4& float4::operator*=(const float4x4& matrix);

    /**
    This will return a COLUMN (m[index][...])
    **/
    float4& operator[](size_t index);

    /**
    This will return a COLUMN (m[index][...])
    **/
    const float4& operator[](size_t index) const;

    static float4x4 createScale(const float3& scale);
    static float4x4 createTranslation(const float3& translation);
    static float4x4 createRotationX(float angleInRadians);
    static float4x4 createRotationY(float angleInRadians);
    static float4x4 createRotationZ(float angleInRadians);
    static float4x4 createRotation(float angleInRadians, const float3& vector);
    static float4x4 createLookAt(const float3& eye, const float3& target, const float3& upVector);
    static float4x4 createPerspective(float fovy, float aspect, float nearPlane, float farPlane);
    static float4x4 createOrthographic(float left, float right, float top, float bottom, float nearPlane, float farPlane);

    static float getDeterminant(const float4x4& matrix);
    static float4x4 inverse(const float4x4& matrix);
    static float4x4 transpose(const float4x4& matrix);
    static float4x4 clamp(const float4x4& matrix, float minValue, float maxValue);

    virtual ~float4x4();
};

