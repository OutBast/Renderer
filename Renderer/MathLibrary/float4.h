#pragma once

class float3;

class float4
{
public:
    float4();
    float4(float value);
    float4(float x, float y, float z);
    float4(float x, float y, float z, float w);
    float4(const float3& val);
    ~float4();


    static float Dot(float4 &a, float4 &b);
    float Dot(float4 &rhs);

#pragma region Overloaded Operators
    float& operator[] (size_t n) { return v[n]; }
    const float& operator[] (size_t n) const { return v[n]; }
#pragma endregion Overloaded Operators

#pragma region Getters & Setters
    float X() const { return x; }
    void X(float val) { x = val; }
    float Y() const { return y; }
    void Y(float val) { y = val; }
    float Z() const { return z; }
    void Z(float val) { z = val; }
    float W() const { return w; }
    void W(float val) { w = val; }
    float R() const { return r; }
    void R(float val) { r = val; }
    float G() const { return g; }
    void G(float val) { g = val; }
    float B() const { return b; }
    void B(float val) { b = val; }
    float A() const { return a; }
    void A(float val) { a = val; }
#pragma endregion Getters & Setters

private:
    union
    {
        struct
        {
            float x, y, z, w;
        };

        struct
        {
            float r, g, b, a;
        };

        float v[4];
    };
};

