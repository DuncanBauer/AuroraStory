#include "pch.h"

#include <aes.h>

#include "Crypto.h"
#include "constants/CryptoConstants.h"
#include "constants/MapleConstants.h"

namespace net
{
	byte rotateRight(byte val, unsigned short shifts)
	{
		shifts &= 7;
		return static_cast<byte>((val >> shifts) | (val << (8 - shifts)));
	}

	byte rotateLeft(byte val, unsigned short shifts)
	{
		shifts &= 7;
		return static_cast<byte>((val << shifts) | (val >> (8 - shifts)));
	}

	void shuffleIv(byte* iv)
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
			value_input = constant::k_shuffle[input];

			new_iv[0] += (constant::k_shuffle[new_iv[1]] - input);
			new_iv[1] -= (new_iv[2] ^ value_input);
			new_iv[2] ^= (constant::k_shuffle[new_iv[3]] + input);
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

	void aesCrypt(byte* buffer, byte* iv, unsigned short size)
	{
		byte temp_iv[16];
		unsigned short pos = 0;
		unsigned short t_pos = 1456;
		unsigned short bytes_amount;

		aes_encrypt_ctx cx[1];
		aes_init();

		while (size > pos)
		{
			memcpy(temp_iv, iv, 16);

			aes_encrypt_key256(constant::k_aesKey, cx);

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

	void decrypt(byte* buffer, byte* iv, unsigned short size)
	{
		aesCrypt(buffer, iv, size);
		shuffleIv(iv);

		byte a;
		byte b;
		byte c;
		unsigned short temp_size;
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

	void encrypt(byte* buffer, byte* iv, unsigned short size)
	{
		byte a;
		byte c;
		unsigned short temp_size;
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

	void createPacketHeader(byte* buffer, byte* iv, unsigned short size)
	{
		unsigned short version = (((iv[3] << 8) | iv[2]) ^ - (constant::k_gameVersion + 1));
		size = version ^ size;

		buffer[0] = version & 0xFF;
		buffer[1] = (version >> 8) & 0xFF;

		buffer[2] = size & 0xFF;
		buffer[3] = (size >> 8) & 0xFF;
	}

	unsigned short getPacketLength(byte* buffer)
	{
		return ((*(unsigned short*)(buffer)) ^ (*(unsigned short*)(buffer + 2)));
	}
}