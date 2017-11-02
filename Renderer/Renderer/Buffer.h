#pragma once

class Buffer
{
public:
    Buffer();
    Buffer(int value);
    Buffer(int width, int height);
    ~Buffer();

    void ClearColor();
    void ClearColor(uint background_value);
    void ClearDepth();

    int Width() const { return m_Width; }
    void Width(int val) { m_Width = val; }
    int Height() const { return m_Height; }
    void Height(int val) { m_Height = val; }
    int MinX() const { return m_MinX; }
    void MinX(int val) { m_MinX = val; }
    int MaxX() const { return m_MaxX; }
    void MaxX(int val) { m_MaxX = val; }
    int MinY() const { return m_MinY; }
    void MinY(int val) { m_MinY = val; }
    int MaxY() const { return m_MaxY; }
    void MaxY(int val) { m_MaxY = val; }

    vector<uint> m_Color;
    vector<float> m_Depth;
protected:
    void CalculateLength();
    void SetSize();

    int m_Width, m_Height, m_MinX, m_MaxX, m_MinY, m_MaxY, m_Length;
};