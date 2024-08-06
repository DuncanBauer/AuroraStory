#include "MapleAESOFB.h"
#include "MapleConstants.h"

namespace util
{
    void MapleAESOFB::aesCrypt(byte* buffer, byte* iv, u16 size)
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

			aes_encrypt_key256(k_aesKey, cx);

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

    void MapleAESOFB::encrypt(byte* buffer, byte* iv, u16 size)
	{
		byte a;
		byte c;
		u16 temp_size;
		u32 loop_counter = 0;

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

    void MapleAESOFB::decrypt(byte* buffer, byte* iv, u16 size)
	{
		aesCrypt(buffer, iv, size);
		shuffleIv(iv);

		byte a;
		byte b;
		byte c;
		u16 temp_size;
		u32 loop_counter = 0;

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

    void MapleAESOFB::createPacketHeader(byte* buffer, byte* iv, u32 size)
	{
		short version = (short)(0xFFFF - k_gameVersion);
		short mapleVersion = (short)(((version >> 8) & 0xFF) | ((version << 8) & 0xFF00));

		int iiv = (iv[3]) & 0xFF;
		iiv |= (iv[2] << 8) & 0xFF00;

		iiv ^= mapleVersion;
		int mlength = ((size << 8) & 0xFF00) | (size >> 8);
		int xoredIv = iiv ^ mlength;

		buffer[0] = (byte)((iiv >> 8) & 0xFF);
		buffer[1] = (byte)(iiv & 0xFF);
		buffer[2] = (byte)((xoredIv >> 8) & 0xFF);
		buffer[3] = (byte)(xoredIv & 0xFF);
	}

    u16 MapleAESOFB::getPacketLength(byte* buffer)
	{
		return ((*(u16*)(buffer)) ^ (*(u16*)(buffer + 2)));
	}

    byte MapleAESOFB::rotateRight(byte val, u16 shifts)
	{
		shifts &= 7;
		return static_cast<byte>((val >> shifts) | (val << (8 - shifts)));
	}

    byte MapleAESOFB::rotateLeft(byte val, u16 shifts)
	{
		shifts &= 7;
		return static_cast<byte>((val << shifts) | (val >> (8 - shifts)));
	}

    void MapleAESOFB::shuffleIv(byte* iv)
	{
		byte new_iv[4] = { 0xF2, 0x53, 0x50, 0xC6 };
		byte input;
		byte value_input;
		u32 full_iv;
		u32 shift;
		u32 loop_counter = 0;

		for (; loop_counter < 4; loop_counter++)
		{
			input = iv[loop_counter];
			value_input = k_shuffle[input];

			new_iv[0] += (k_shuffle[new_iv[1]] - input);
			new_iv[1] -= (new_iv[2] ^ value_input);
			new_iv[2] ^= (k_shuffle[new_iv[3]] + input);
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
}