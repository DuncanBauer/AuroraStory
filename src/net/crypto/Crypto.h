#pragma once

#include <vector>

namespace net
{
	typedef unsigned char byte;

	void decrypt(byte* buffer, byte* iv, unsigned short size);
	void encrypt(byte* buffer, byte* iv, unsigned short size);
	void createPacketHeader(byte* buffer, byte* iv, unsigned short size);
	unsigned short getPacketLength(byte* buffer);
}