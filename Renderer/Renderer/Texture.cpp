#include "stdafx.h"
#include "Texture.h"

Texture::Texture() : Texture(0, 0, "none") {}

Texture::Texture(int width, int height, std::string name) : width{ width }, height{ height }, size{ height*width }, name{ name }
{
    //arr = new float3[size];
    vec = std::vector<float3>(size);
    buffer = TgaBuffer(width, height);
    buffer.LoadTexture(name);
    buffer.Save("bartekblabla.tga");

    //Data::Instance().textures[name] = this;
}

Texture::Texture(const Texture & other) : width{ other.width }, height{ other.height }, size{ other.size }
{
    //arr = new float3[size];
    vec = std::vector<float3>(size);
    for (int i = 0; i < size; ++i)
    {
        //buffer[i] = other.vec[i];
        //arr[i] = float3{ other.arr[i] };
    }
}

Texture::~Texture()
{
    //delete[] arr;
}

float3 & Texture::operator[](unsigned int at)
{
    if (at >= size || at < 0) { throw std::exception("Texture: array out of bounds"); }

    return UintToColor(buffer.m_Color[at]);
}

const float3 & Texture::operator[](unsigned int at) const
{
    if (at >= size || at < 0) { //throw std::exception("Texture: array out of bounds"); }
        return{ 0,0,0 };
    }

    return UintToColor(buffer.m_Color[at]);
}

float3 Texture::getColor(const float3 & coord) const
{
    int i = (int)(coord.x * width) + (int)(coord.y * height)*width;
    return (*this)[i];
}