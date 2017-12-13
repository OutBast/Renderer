#include "stdafx.h"
#include "TgaBuffer.h"
#include "Texture.h"


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

bool TgaBuffer::LoadTexture(const std::string& filename)
{
    SetHeader();

    FILE *f;
    fopen_s(&f, filename.c_str(), "rb+");
    if (!f) return false;

    fread(m_Header, sizeof(unsigned short), 9, f);

    int width = m_Header[6];
    int height = m_Header[7];
    int len = width * height;
    unsigned int * texBuffer = new unsigned int[len];

    fread(texBuffer, sizeof(unsigned int), len, f);

    //Texture *txt = new Texture{ width, height, textureName };
    for (int i = 0; i < len; ++i)
    {
        m_Color[i] = texBuffer[i];
    }

    fclose(f);

    return true;
}
