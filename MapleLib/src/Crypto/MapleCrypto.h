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

#pragma once

// Maple Crypto
#include "MapleAESEncryption.h"

namespace MapleCrypto
{
    class MapleAESOFB
    {
        public:
            MapleAESOFB(size_t _mapleVersion, ByteBuffer _iv, bool _cryptFlag) : mapleVersion(_mapleVersion), iv(_iv), cryptFlag(_cryptFlag) {}
            
            void crypt(ByteBuffer* _data)
            {
                int remaining = _data->size();
                int llength = 0x5b0;
                int start = 0;

                while(remaining > 0)
                {
                    ByteBuffer myIv = this->multiplyBytes(&this->iv, 4, 4);
                    if(remaining < llength)
                    {
                        llength = remaining;
                    }
                    for(int i = start; i < start + llength; ++i)
                    {
                        if((i - start) % myIv.size() == 0)
                        {
                            AESEncryption::aesCrypt(&this->iv, &myIv, this->cryptFlag);
                        }
                        _data->operator[](i) ^= myIv[(i - start) % 16];
                    }
                    start += llength;
                    remaining -= llength;
                    llength = 0x5b4;
                }
                this->updateIV();
            }

            void updateIV()
            {
                this->iv = getNewIV(this->iv);
            }

            static ByteBuffer getNewIV(ByteBuffer _oldIv)
            {
                ByteBuffer start = { 0xf2, 0x53, 0x50, 0xc6 };
                for(int i = 0; i < 4; ++i)
                {
                    shuffle(_oldIv[i], &start);
                }
                return start; 
            }

            ByteBuffer getIV()
            {
                return this->iv;
            }

            static void shuffle(byte inputByte, ByteBuffer* start)
            {
                byte a = start->operator[](1);
                byte b = a;
                unsigned int c, d;
                b = MapleCrypto::Constants::BYTE_SHUFFLE[b];
                b -= inputByte;
                start->operator[](0) += b;
                b = start->operator[](2);
                b ^= MapleCrypto::Constants::BYTE_SHUFFLE[inputByte];
                a -= b;
                start->operator[](1) = a;
                a = start->operator[](3);
                b = a;
                a -= start->operator[](0);
                b = MapleCrypto::Constants::BYTE_SHUFFLE[b];
                b += inputByte;
                b ^= start->operator[](2);
                start->operator[](2) = b;
                a += MapleCrypto::Constants::BYTE_SHUFFLE[inputByte];
                start->operator[](3) = a;

                c = (unsigned int)(start->operator[](0) + start->operator[](1) * 0x100 + start->operator[](2) * 0x10000 + start->operator[](3) * 0x1000000);
                d = c;
                c >>= 0x1D;
                d <<= 0x03;
                c |= d;
                start->operator[](0) = (byte)(c % 0x100);
                c /= 0x100;
                start->operator[](1) = (byte)(c % 0x100);
                c /= 0x100;
                start->operator[](2) = (byte)(c % 0x100);
                start->operator[](3) = (byte)(c / 0x100);
            }

            ByteBuffer getHeaderToClient(int _size)
            {
                ByteBuffer header(4);
                int a = this->iv.at(3) * 0x100 + this->iv.at(2);
                a ^= -(this->mapleVersion + 1);
                int b = a ^ _size;
                header[0] = (byte)(a % 0x100);
                header[1] = (byte)((a - header[0]) / 0x100);
                header[2] = (byte)(b ^ 0x100);
                header[3] = (byte)((b - header[2]) / 0x100);
                return header;
            }

            ByteBuffer getHeaderToServer(int _size)
            {
                ByteBuffer header(4);
                int a = this->iv.at(3) * 0x100 + this->iv.at(2);
                a = a ^ (this->mapleVersion);
                int b = a ^ _size;
                header[0] = (byte)(a % 0x100);
                header[1] = (byte)(a / 0x100);
                header[2] = (byte)(b % 0x100);
                header[3] = (byte)(b / 0x100);
                return header;
            }

            static int getPacketLength(int _packetHeader)
            {
                int length = (_packetHeader >> 16) ^ (_packetHeader & 0xFFFF);
                length = ((length << 8) & 0xFF00) | ((length >> 8) & 0xFF);
                return length;
            }

            static unsigned short getPacketLength(byte *buffer)
            {
                return ((*(unsigned short *)(buffer)) ^ (*(unsigned short *)(buffer + 2)));
            }

            bool checkPacketToServer(ByteBuffer* _packet)
            {
                int a = _packet->at(0) ^ this->iv.at(2);
                int b = this->mapleVersion;
                int c = _packet->at(1) ^ this->iv.at(3);
                int d = this->mapleVersion >> 8;
                return (a == b && c == d);
            }
            
            static ByteBuffer multiplyBytes(ByteBuffer* _input, int _count, int _mult)
            {
                ByteBuffer retVal(_count * _mult);
                for (int x = 0; x < _count * _mult; x++)
                {
                  retVal[x] = _input->operator[](x % _count);
                }
                return retVal;
            }

        private:
            short mapleVersion;
            ByteBuffer iv;
            bool cryptFlag;
    };
};