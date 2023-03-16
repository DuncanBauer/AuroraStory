#pragma once

#include "Maple.h"
#include <vector>

using byte = unsigned char;
using ByteBuffer = std::vector<byte>;

namespace Util
{
	class BitTool
	{
	public:
		// Bitwise Operations
		static byte RollLeft(byte val, int num)
		{
			num &= 7;
			return static_cast<unsigned char>((val << num) | (val >> (8 - num)));
		}
		static byte RollRight(byte val, int num)
		{
			num &= 7;
			return (val >> num) | (val << (8 - num));
			return static_cast<unsigned char>((val >> num) | (val << (8 - num)));
		}

		// Bytewise Operations
		static unsigned int RollLeft(unsigned int x, byte n)
		{
			return (unsigned int)(((x) << (n)) | ((x) >> (32 - (n))));
		}

		static unsigned int RollRight(unsigned int x, byte n)
		{
			return (unsigned int)(((x) >> (n)) | ((x) << (32 - (n))));
		}
	private:
	};
}