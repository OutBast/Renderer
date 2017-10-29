#pragma once
#include "Buffer.h"
#include "ISaveable.h"

class TgaBuffer : public Buffer, public ISaveable
{
public:
	TgaBuffer();
	TgaBuffer(int value);
	TgaBuffer(int width, int height);
	~TgaBuffer();

	void Save(const string file_name) override;

private:
	void SetHeader();

	ushort m_Header[9] =
	{
		0x0000, 0x0002, 0x0000,
		0x0000, 0x0000, 0x0000,
		0x0100, 0x0100, 0x0820 // width, height, ...
	};
};

