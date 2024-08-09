#pragma once
#include "Typedefs.h"

namespace util
{
    class MapleAESOFB
    {
    public:
        MapleAESOFB() = delete;

		static void aesCrypt(byte* buffer, byte* iv, u16 size);
		static void encrypt(byte* buffer, byte* iv, u16 size);
		static void decrypt(byte* buffer, byte* iv, u16 size);
		static void createPacketHeader(byte* buffer, byte* iv, u32 size);
		static u16  getPacketLength(byte* buffer);

    private:
		static byte rotateRight(byte val, u16 shifts);
		static byte rotateLeft(byte val, u16 shifts);
		static void shuffleIv(byte* iv);
    };
}