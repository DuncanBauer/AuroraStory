#pragma once

#include "Maple.h"

namespace Crypto
{
	class MapleCrypto {
		public:
			static void ShuffleIv(unsigned char* iv);
			static void CreatePacketHeader(unsigned char* buffer, unsigned char* iv, unsigned short size);
			static unsigned short GetPacketLength(unsigned char* buffer);
			static void Crypt(unsigned char* buffer, unsigned char* iv, size_t size);
			static void MapleDecrypt(unsigned char* buffer, unsigned char* iv, size_t size);
			static void MapleEncrypt(unsigned char* buffer, unsigned char* iv, size_t size);
	};
}
