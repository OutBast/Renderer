#include "stdafx.h"
#include "Buffer.h"


Buffer::Buffer() : m_Width(512), m_Height(512)
{
    CalculateLength();
    SetSize();
    ClearColor();
    ClearDepth();
}


Buffer::Buffer(int value) : m_Width(value), m_Height(value)
{
    CalculateLength();
    SetSize();
    ClearColor();
    ClearDepth();
}

Buffer::Buffer(int width, int height) : m_Width(width), m_Height(height)
{
    CalculateLength();
    SetSize();
    ClearColor();
    ClearDepth();
}

Buffer::~Buffer()
{
    m_Color.clear();
    m_Depth.clear();
}

void Buffer::ClearColor()
{
    for (auto& pixel : m_Color)
    {
        pixel = 0x00000000;
    }
}

void Buffer::ClearColor(uint background_value)
{
    for (auto& pixel : m_Color)
    {
        pixel = background_value;
    }
}

void Buffer::ClearDepth()
{
    for (auto& pixel : m_Depth)
    {
        pixel = -1.0f;
    }
}

void Buffer::CalculateLength()
{
    m_Length = m_Width * m_Height;
}

void Buffer::SetSize()
{
    m_Color.resize(m_Length);
    m_Depth.resize(m_Length);
}
