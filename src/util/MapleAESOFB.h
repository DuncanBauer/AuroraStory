#pragma once

#include <vector>

#include "aes/aes.h"
#include "Typedefs.h"

namespace util
{
    class MapleAESOFB
    {
    public:
        MapleAESOFB() = delete;

        static inline void encrypt(byte* buffer, byte* iv, u16 size)
		{
			byte a;
			byte c;
			u16 temp_size;
			int loop_counter = 0;

			for (; loop_counter < 3; ++loop_counter)
			{
				a = 0;
				for (temp_size = size; temp_size > 0; --temp_size)
				{
					c = buffer[size - temp_size];
					c = rotateLeft(c, 3);
					c = static_cast<byte>(c + temp_size);
					c = c ^ a;
					a = c;
					c = rotateRight(a, temp_size);
					c = c ^ 0xFF;
					c = c + 0x48;
					buffer[size - temp_size] = c;
				}
				a = 0;
				for (temp_size = size; temp_size > 0; --temp_size)
				{
					c = buffer[temp_size - 1];
					c = rotateLeft(c, 4);
					c = static_cast<byte>(c + temp_size);
					c = c ^ a;
					a = c;
					c = c ^ 0x13;
					c = rotateRight(c, 3);
					buffer[temp_size - 1] = c;
				}
			}

			aesCrypt(buffer, iv, size);
			shuffleIv(iv);
		}

        static inline void decrypt(byte* buffer, byte* iv, u16 size)
		{
			aesCrypt(buffer, iv, size);
			shuffleIv(iv);

			byte a;
			byte b;
			byte c;
			u16 temp_size;
			int loop_counter = 0;

			for (; loop_counter < 3; ++loop_counter)
			{
				a = 0;
				b = 0;
				for (temp_size = size; temp_size > 0; --temp_size)
				{
					c = buffer[temp_size - 1];
					c = rotateLeft(c, 3);
					c = c ^ 0x13;
					a = c;
					c = c ^ b;
					c = static_cast<byte>(c - temp_size);
					c = rotateRight(c, 4);
					b = a;
					buffer[temp_size - 1] = c;
				}

				a = 0;
				b = 0;
				for (temp_size = size; temp_size > 0; --temp_size)
				{
					c = buffer[size - temp_size];
					c = c - 0x48;
					c = c ^ 0xFF;
					c = rotateLeft(c, temp_size);
					a = c;
					c = c ^ b;
					c = static_cast<byte>(c - temp_size);
					c = rotateRight(c, 3);
					b = a;
					buffer[size - temp_size] = c;
				}
			}
		}

        static inline void createPacketHeader(byte* buffer, byte* iv, u16 size)
		{
			u16 version = (((iv[3] << 8) | iv[2]) ^ -(k_gameVersion + 1));
			size = version ^ size;

			buffer[0] = version & 0xFF;
			buffer[1] = (version >> 8) & 0xFF;

			buffer[2] = size & 0xFF;
			buffer[3] = (size >> 8) & 0xFF;
		}

        static inline u16 getPacketLength(byte* buffer)
		{
			return ((*(u16*)(buffer)) ^ (*(u16*)(buffer + 2)));
		}

    private:
        static inline byte rotateRight(byte val, u16 shifts)
		{
			shifts &= 7;
			return static_cast<byte>((val >> shifts) | (val << (8 - shifts)));
		}

        static inline byte rotateLeft(byte val, u16 shifts)
		{
			shifts &= 7;
			return static_cast<byte>((val << shifts) | (val >> (8 - shifts)));
		}

        static inline void shuffleIv(byte* iv)
		{
			byte new_iv[4] = { 0xF2, 0x53, 0x50, 0xC6 };
			byte input;
			byte value_input;
			unsigned int full_iv;
			unsigned int shift;
			int loop_counter = 0;

			for (; loop_counter < 4; loop_counter++)
			{
				input = iv[loop_counter];
				value_input = m_shuffle[input];

				new_iv[0] += (m_shuffle[new_iv[1]] - input);
				new_iv[1] -= (new_iv[2] ^ value_input);
				new_iv[2] ^= (m_shuffle[new_iv[3]] + input);
				new_iv[3] -= (new_iv[0] - value_input);

				full_iv = (new_iv[3] << 24) | (new_iv[2] << 16) | (new_iv[1] << 8) | new_iv[0];
				shift = (full_iv >> 0x1D) | (full_iv << 0x03);

				new_iv[0] = static_cast<byte>(shift & 0xFFu);
				new_iv[1] = static_cast<byte>((shift >> 8) & 0xFFu);
				new_iv[2] = static_cast<byte>((shift >> 16) & 0xFFu);
				new_iv[3] = static_cast<byte>((shift >> 24) & 0xFFu);
			}

			// set iv
			memcpy(iv, new_iv, 4);
			memcpy(iv + 4, new_iv, 4);
			memcpy(iv + 8, new_iv, 4);
			memcpy(iv + 12, new_iv, 4);
		}

        static inline void aesCrypt(byte* buffer, byte* iv, u16 size)
		{
			byte temp_iv[16];
			u16 pos = 0;
			u16 t_pos = 1456;
			u16 bytes_amount;

			aes_encrypt_ctx cx[1];
			aes_init();

			while (size > pos)
			{
				memcpy(temp_iv, iv, 16);

				aes_encrypt_key256(m_aesKey, cx);

				if (size > (pos + t_pos))
				{
					bytes_amount = t_pos;
				}
				else
				{
					bytes_amount = size - pos;
				}

				aes_ofb_crypt(buffer + pos, buffer + pos, bytes_amount, temp_iv, cx);

				pos += t_pos;
				t_pos = 1460;
			}
		}

	private:
		// Constant used in WZ offset encryption
		static constexpr uint32_t m_wzOffsetConstant = 0x581C3F6D;

		// IV used to create the WzKey for GMS
		static constexpr byte m_wzFileKeyIv[4] = { 0x4D, 0x23, 0xC7, 0x2B };

		static constexpr byte m_aesKey[32] =
		{
			0x13, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xB4, 0x00, 0x00, 0x00,
			0x1B, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00
		};

		// ShuffleBytes used by MapleStory to generate a new IV
		static constexpr byte m_shuffle[256] =
		{//16 * 16
			0xEC, 0x3F, 0x77, 0xA4, 0x45, 0xD0, 0x71, 0xBF, 0xB7, 0x98, 0x20, 0xFC, 0x4B, 0xE9, 0xB3, 0xE1,
			0x5C, 0x22, 0xF7, 0x0C, 0x44, 0x1B, 0x81, 0xBD, 0x63, 0x8D, 0xD4, 0xC3, 0xF2, 0x10, 0x19, 0xE0,
			0xFB, 0xA1, 0x6E, 0x66, 0xEA, 0xAE, 0xD6, 0xCE, 0x06, 0x18, 0x4E, 0xEB, 0x78, 0x95, 0xDB, 0xBA,
			0xB6, 0x42, 0x7A, 0x2A, 0x83, 0x0B, 0x54, 0x67, 0x6D, 0xE8, 0x65, 0xE7, 0x2F, 0x07, 0xF3, 0xAA,
			0x27, 0x7B, 0x85, 0xB0, 0x26, 0xFD, 0x8B, 0xA9, 0xFA, 0xBE, 0xA8, 0xD7, 0xCB, 0xCC, 0x92, 0xDA,
			0xF9, 0x93, 0x60, 0x2D, 0xDD, 0xD2, 0xA2, 0x9B, 0x39, 0x5F, 0x82, 0x21, 0x4C, 0x69, 0xF8, 0x31,
			0x87, 0xEE, 0x8E, 0xAD, 0x8C, 0x6A, 0xBC, 0xB5, 0x6B, 0x59, 0x13, 0xF1, 0x04, 0x00, 0xF6, 0x5A,
			0x35, 0x79, 0x48, 0x8F, 0x15, 0xCD, 0x97, 0x57, 0x12, 0x3E, 0x37, 0xFF, 0x9D, 0x4F, 0x51, 0xF5,
			0xA3, 0x70, 0xBB, 0x14, 0x75, 0xC2, 0xB8, 0x72, 0xC0, 0xED, 0x7D, 0x68, 0xC9, 0x2E, 0x0D, 0x62,
			0x46, 0x17, 0x11, 0x4D, 0x6C, 0xC4, 0x7E, 0x53, 0xC1, 0x25, 0xC7, 0x9A, 0x1C, 0x88, 0x58, 0x2C,
			0x89, 0xDC, 0x02, 0x64, 0x40, 0x01, 0x5D, 0x38, 0xA5, 0xE2, 0xAF, 0x55, 0xD5, 0xEF, 0x1A, 0x7C,
			0xA7, 0x5B, 0xA6, 0x6F, 0x86, 0x9F, 0x73, 0xE6, 0x0A, 0xDE, 0x2B, 0x99, 0x4A, 0x47, 0x9C, 0xDF,
			0x09, 0x76, 0x9E, 0x30, 0x0E, 0xE4, 0xB2, 0x94, 0xA0, 0x3B, 0x34, 0x1D, 0x28, 0x0F, 0x36, 0xE3,
			0x23, 0xB4, 0x03, 0xD8, 0x90, 0xC8, 0x3C, 0xFE, 0x5E, 0x32, 0x24, 0x50, 0x1F, 0x3A, 0x43, 0x8A,
			0x96, 0x41, 0x74, 0xAC, 0x52, 0x33, 0xF0, 0xD9, 0x29, 0x80, 0xB1, 0x16, 0xD3, 0xAB, 0x91, 0xB9,
			0x84, 0x7F, 0x61, 0x1E, 0xCF, 0xC5, 0xD1, 0x56, 0x3D, 0xCA, 0xF4, 0x05, 0xC6, 0xE5, 0x08, 0x49
		};
    };
}