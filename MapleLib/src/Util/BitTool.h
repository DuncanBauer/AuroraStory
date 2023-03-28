#pragma once

#include "Maple.h"
#include <vector>

namespace Util
{
	class BitTool
	{
		public:
			// Bitwise Conversions
			template<typename T>
			static T ToIntType(unsigned char* bytes, int startIndex)
			{
				T value = 0;
				for (int i = startIndex; i < startIndex + sizeof(T); i++)
					value |= static_cast<T>(bytes[i]) << (i * 8);
				return value;
			}

			template<typename T>
			static T ToIntType(unsigned char* bytes)
			{
				T value = 0;
				for (int i = 0; i < sizeof(T); i++)
					value |= static_cast<T>(bytes[i]) << (i * 8);
				return value;
			}

			// Bitwise Rotations
			template<typename T>
			static T RollLeft(T val, int num) {
				int dataSize = sizeof(T) - 1;
				num &= dataSize;
				return static_cast<T>(val << num | val >> (dataSize - num));
			}

			template<typename T>
			static T RollRight(T val, int num) {
				int dataSize = sizeof(T) - 1;
				num &= dataSize;
				return static_cast<T>(val >> num | val << (dataSize - num));
			}
	};
}