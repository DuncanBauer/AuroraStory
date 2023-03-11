/*********************************************************************************
* AuroraSource - A C++ MapleStory Server Emulator
* Copyright(C) 2021 Duncan Bauer <duncanebauer@gmail.com>
*
* This program is free software : you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************************/

#ifndef MAPLECUSTOMENCRYPTION_H
#define MAPLECUSTOMENCRYPTION_H

// Maple Crypto
#include "MapleCryptoConstants.h"

// I honestly have no idea what's really going on in here.
// Thank god for the OdinMS people that are smart than me
namespace MapleCrypto
{
    namespace CustomEncryption
    {
        // Function prototypes
        inline void encrypt(ByteBuffer* _data, size_t _length);
        inline void decrypt(ByteBuffer* _data, size_t _length);

        // Hide rol and ror functions
        namespace {
            // Function prototypes
            inline byte rol(byte _val, size_t _num);
            inline byte ror(byte _val, size_t _num);

            byte rol(byte _val, size_t _num)
            {
                // size_t highbit;
                // for(size_t i = 0; i < _num; ++i)
                // {
                //     highbit = ((_val & 0x80) != 0 ? 1 : 0);
                //     _val <<= 1;
                //     _val |= (byte)highbit;
                // }
                // return _val;
                _num &= 7;
                return static_cast<unsigned char>((_val << _num) | (_val >> (8 - _num)));
            }

            byte ror(byte _val, size_t _num)
            {
                // size_t lowbit;
                // for(size_t i = 0; i < _num; ++i)
                // {
                //     lowbit = ((_val & 1) != 0 ? 1 : 0);
                //     _val >>= 1;
                //     _val |= (byte)(lowbit << 7);
                // }
                // return _val;
                _num &= 7;
                return static_cast<unsigned char>((_val >> _num) | (_val << (8 - _num)));
            }
        };

        void encrypt(ByteBuffer* _data, size_t _length)
        {
            size_t j;
            byte a;
            byte c;

            for(size_t i = 0; i < 3; ++i)
            {
                a = 0;
                for(j = _length; j > 0; j--)
                {
                    c = _data->at(_length - j);
                    c = rol(c, 3);
                    c = (byte)(c + j);
                    c ^= a;
                    a = c;
                    c = ror(a, j);
                    c ^= 0xFF;
                    c += 0x48;
                    _data->operator[](_length - j) = c;
                }
                a = 0;
                for(j = _length; j > 0; --j)
                {
                    c = _data->at(j - 1);
                    c = rol(c, 4);
                    c = (byte)(c + j);
                    c ^= a;
                    a = c;
                    c ^= 0x13;
                    c = ror(c, 3);
                    _data->operator[](j - 1) = c;
                }
            }
        }

        void decrypt(ByteBuffer* _data, size_t _length)
        {
            size_t j;
            byte a;
            byte b;
            byte c;
            for(size_t i = 0; i < 3; ++i)
            {
                a = 0;
                b = 0;
                for(j = _length; j > 0; --j)
                {
                    c = _data->at(j - 1);
                    c = rol(c, 3);
                    c ^= 0x13;
                    a = c;
                    c ^= b;
                    c = (byte)(c - j);
                    c = ror(c, 4);
                    b = a;
                    _data->operator[](j - 1) = c;
                }
                a = 0;
                b = 0;
                for(j = _length; j > 0; --j)
                {
                    c = _data->at(_length - j);
                    c -= 0x48;
                    c ^= 0xFF;
                    c = rol(c, j);
                    a = c;
                    c ^= b;
                    c = (c - j);
                    c = ror(c, 3);
                    b = a;
                    _data->operator[](_length - j) = c;
                }
            }
        }
    };
};

#endif