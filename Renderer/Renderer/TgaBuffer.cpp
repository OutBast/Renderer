#include "stdafx.h"
#include "TgaBuffer.h"


TgaBuffer::TgaBuffer() : Buffer()
{ }


TgaBuffer::TgaBuffer(int value) : Buffer(value)
{ }

TgaBuffer::TgaBuffer(int width, int height) : Buffer(width, height)
{ }

TgaBuffer::~TgaBuffer()
{ }

void TgaBuffer::SetHeader()
{
    m_Header[6] = m_Width;
    m_Header[7] = m_Height;
}

void TgaBuffer::Save(const string file_name)
{
    SetHeader();

    FILE *tga_file = nullptr;
    fopen_s(&tga_file, file_name.c_str(), "wb+");

    fwrite(m_Header, 2, 9, tga_file);
    fwrite(m_Color.data(), 4, m_Length, tga_file);

    fclose(tga_file);
}