#pragma once

// Project headers
#include "MapleCrypto.h"
#include "../Util/BitTool.h"

// C++ headers
#include <iostream>

// Third party headers
#include "aes/aes.h"

namespace Crypto
{
    void MapleCrypto::ShuffleIv(unsigned char* iv)
    {
        unsigned char new_iv[4] = { 0xF2, 0x53, 0x50, 0xC6 };
        unsigned char input;
        unsigned char value_input;
        unsigned int full_iv;
        unsigned int shift;

        for (int loop_counter = 0; loop_counter < 4; loop_counter++)
        {
            input = iv[loop_counter];
            value_input = Constants::BYTE_SHUFFLE[input];

            new_iv[0] += (Constants::BYTE_SHUFFLE[new_iv[1]] - input);
            new_iv[1] -= (new_iv[2] ^ value_input);
            new_iv[2] ^= (Constants::BYTE_SHUFFLE[new_iv[3]] + input);
            new_iv[3] -= (new_iv[0] - value_input);

            full_iv = (new_iv[3] << 24) | (new_iv[2] << 16) | (new_iv[1] << 8) | new_iv[0];
            shift = (full_iv >> 0x1D) | (full_iv << 0x03);

            new_iv[0] = static_cast<unsigned char>(shift & 0xFFu);
            new_iv[1] = static_cast<unsigned char>((shift >> 8) & 0xFFu);
            new_iv[2] = static_cast<unsigned char>((shift >> 16) & 0xFFu);
            new_iv[3] = static_cast<unsigned char>((shift >> 24) & 0xFFu);
        }

        // set iv
        memcpy(iv, new_iv, 4);
        memcpy(iv + 4, new_iv, 4);
        memcpy(iv + 8, new_iv, 4);
        memcpy(iv + 12, new_iv, 4);
    }

    void MapleCrypto::CreatePacketHeader(unsigned char* buffer, unsigned char* iv, unsigned short size)
    {
        unsigned short version = (((iv[3] << 8) | iv[2]) ^ -(Constants::MAPLE_VERSION + 1));
        size = version ^ size;

        buffer[0] = version & 0xFF;
        buffer[1] = (version >> 8) & 0xFF;

        buffer[2] = size & 0xFF;
        buffer[3] = (size >> 8) & 0xFF;
    }

    unsigned short MapleCrypto::GetPacketLength(unsigned char* buffer)
    {
        return ((*(unsigned short*)(buffer)) ^ (*(unsigned short*)(buffer + 2)));
    }

    // AES ENCRYPTION
    void MapleCrypto::Crypt(unsigned char* data, unsigned char* iv, size_t size) {
        unsigned char temp_iv[16];
        size_t pos = 0;
        size_t t_pos = 1456;
        size_t bytes_amount;

        aes_encrypt_ctx cx[1];
        aes_init();

        while (size > pos)
        {
            memcpy(temp_iv, iv, 16);
            aes_encrypt_key256(Constants::MAPLESTORY_AES_KEY, cx);

            if (size > (pos + t_pos))
            {
                bytes_amount = t_pos;
            }
            else
            {
                bytes_amount = size - pos;
            }

            aes_ofb_crypt(data + pos, data + pos, bytes_amount, temp_iv, cx);

            pos += t_pos;
            t_pos = 1460;
        }
    }

    void MapleCrypto::MapleEncrypt(unsigned char* data, unsigned char* iv, size_t size)
    {
        int j;
        int length = size;
        char a;
        char c;

        for (int i = 0; i < 3; ++i)
        {
            a = 0;
            for (j = length; j > 0; j--)
            {
                c = data[length - j];
                c = Util::BitTool::RollLeft(c, 3);
                c = (char)(c + j);
                c ^= a;
                a = c;
                c = Util::BitTool::RollRight(a, j);
                c ^= 0xFF;
                c += 0x48;
                data[length - j] = c;
            }
            a = 0;

            for (j = length; j > 0; --j)
            {
                c = data[j - 1];
                c = Util::BitTool::RollLeft(c, 4);
                c = (char)(c + j);
                c ^= a;
                a = c;
                c ^= 0x13;
                c = Util::BitTool::RollRight(c, 3);
                data[j - 1] = c;
            }
        }
        ShuffleIv(data);
    }

    void MapleCrypto::MapleDecrypt(unsigned char* data, unsigned char* iv, size_t size)
    {
        Crypt(data, iv, size);

        for (int i = 0; i < size; ++i)
        {
            std::cout << (unsigned int)data[i] << ' ';
        }
        std::cout << "\n\n";


        int j;
        int length = size;
        char a;
        char b;
        char c;
                    
        for (int i = 0; i < 3; ++i)
        {
            a = 0;
            b = 0;
            for (j = length; j > 0; --j)
            {
                c = data[j - 1];
                c = Util::BitTool::RollLeft(c, 3);
                c ^= 0x13;
                a = c;
                c ^= b;
                c = (char)(c - j);
                c = Util::BitTool::RollRight(c, 4);
                b = a;
                data[j - 1] = c;
            }
            a = 0;
            b = 0;
                        
            for (j = length; j > 0; --j)
            {
                c = data[length - j];
                c -= 0x48;
                c ^= 0xFF;
                c = Util::BitTool::RollLeft(c, j);
                a = c;
                c ^= b;
                c = (c - j);
                c = Util::BitTool::RollRight(c, 3);
                b = a;
                data[length - j] = c;
            }
        }
    }
}
