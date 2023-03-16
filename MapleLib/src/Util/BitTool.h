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
		// Bitwise Conversions
		static uint16_t ToUInt16(ByteBuffer bytes, int startIndex)
		{
			uint16_t value = 0;
			for (int i = startIndex; i < startIndex + 2; i++)
			{
				value |= static_cast<uint16_t>(bytes[i]) << (i * 8);
			}
			return value;
		}

		static int16_t ToInt16(ByteBuffer bytes, int startIndex)
		{
			int16_t value = 0;
			for (int i = startIndex; i < startIndex + 2; i++)
			{
				value |= static_cast<int16_t>(bytes[i]) << (i * 8);
			}
			return value;
		}

		static uint32_t ToUInt32(ByteBuffer bytes, int startIndex)
		{
			uint32_t value = 0;
			for (int i = startIndex; i < startIndex + 4; i++)
			{
				value |= static_cast<uint32_t>(bytes[i]) << (i * 8);
			}
			return value;
		}

		static int32_t ToInt32(ByteBuffer bytes, int startIndex)
		{
			int32_t value = 0;
			for (int i = startIndex; i < startIndex + 4; i++)
			{
				value |= static_cast<int32_t>(bytes[i]) << (i * 8);
			}
			return value;
		}

		static uint64_t ToUInt64(ByteBuffer bytes, int startIndex)
		{
			uint64_t value = 0;
			for (int i = startIndex; i < startIndex + 8; i++)
			{
				value |= static_cast<uint64_t>(bytes[i]) << (i * 8);
			}
			return value;
		}

		static int64_t ToInt64(ByteBuffer bytes, int startIndex)
		{
			int64_t value = 0;
			for (int i = startIndex; i < startIndex + 8; i++)
			{
				value |= static_cast<int64_t>(bytes[i]) << (i * 8);
			}
			return value;
		}

		// Bitwise Rotations
		static byte RollLeft(byte val, int num)
		{
			num &= 7; // Ensures number of bits shifted is less than 8
			return static_cast<byte>(val << num | val >> (8 - num));
		}

		static byte RollRight(byte val, int num)
		{
			num &= 7; // Ensures number of bits shifted is less than 8
			return static_cast<byte>(val >> num | val << (8 - num));
		}

		static char RollLeft(char val, int num)
		{
			num &= 7; // Ensures number of bits shifted is less than 8
			return static_cast<char>(val << num | val >> (8 - num));
		}

		static char RollRight(char val, int num)
		{
			num &= 7; // Ensures number of bits shifted is less than 8
			return static_cast<char>(val >> num | val << (8 - num));
		}

		static uint16_t RollLeft(uint16_t val, int num)
		{
			num &= 15; // Ensures number of bits shifted is less than 16
			return static_cast<uint16_t>(val << num | val >> (16 - num));
		}

		static uint16_t RollRight(uint16_t val, int num)
		{
			num &= 15; // Ensures number of bits shifted is less than 16
			return static_cast<uint16_t>(val >> num | val << (16 - num));
		}

		static int16_t RollLeft(int16_t val, int num)
		{
			num &= 15; // Ensures number of bits shifted is less than 16
			return static_cast<int16_t>(val << num | val >> (16 - num));
		}

		static int16_t RollRight(int16_t val, int num)
		{
			num &= 15; // Ensures number of bits shifted is less than 16
			return static_cast<int16_t>(val >> num | val << (16 - num));
		}

		static uint32_t RollLeft(uint32_t val, int num)
		{
			num &= 31; // Ensures number of bits shifted is less than 32
			return static_cast<uint32_t>(val << num | val >> (32 - num));
		}

		static uint32_t RollRight(uint32_t val, int num)
		{
			num &= 31; // Ensures number of bits shifted is less than 32
			return static_cast<uint32_t>(val >> num | val << (32 - num));
		}

		static int32_t RollLeft(int32_t val, int num)
		{
			num &= 31; // Ensures number of bits shifted is less than 32
			return static_cast<int32_t>(val << num | val >> (32 - num));
		}

		static int32_t RollRight(int32_t val, int num)
		{
			num &= 31; // Ensures number of bits shifted is less than 32
			return static_cast<int32_t>(val >> num | val << (32 - num));
		}

		static uint64_t RollLeft(uint64_t val, int num)
		{
			num &= 63; // Ensures number of bits shifted is less than 64
			return static_cast<uint64_t>(val << num | val >> (64 - num));
		}

		static uint64_t RollRight(uint64_t val, int num)
		{
			num &= 63; // Ensures number of bits shifted is less than 64
			return static_cast<uint64_t>(val >> num | val << (64 - num));
		}

		static int64_t RollLeft(int64_t val, int num)
		{
			num &= 63; // Ensures number of bits shifted is less than 64
			return static_cast<int64_t>(val << num | val >> (64 - num));
		}

		static int64_t RollRight(int64_t val, int num)
		{
			num &= 63; // Ensures number of bits shifted is less than 64
			return static_cast<int64_t>(val >> num | val << (64 - num));
		}
	};
}