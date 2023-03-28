#pragma once

#include "Maple.h"

#include "aes/aes.h"

namespace Net
{
	namespace Crypto
	{
		class AURORA_MAPLE_API MapleAES
		{
		private:
			unsigned char* m_IV;
			short m_MapleVersion;

        private:
            static void Shuffle(char inputByte, unsigned char* start)
            {
                char a = start[1];
                char b = a;
                unsigned int c, d;
                b = Constants::BYTE_SHUFFLE[b];
                b -= inputByte;
                start[0] += b;
                b = start[2];
                b ^= Constants::BYTE_SHUFFLE[inputByte];
                a -= b;
                start[1] = a;
                a = start[3];
                b = a;
                a -= start[0];
                b = Constants::BYTE_SHUFFLE[b];
                b += inputByte;
                b ^= start[2];
                start[2] = b;
                a += Constants::BYTE_SHUFFLE[inputByte];
                start[3] = a;

                c = (unsigned int)(start[0] + start[1] * 0x100 + start[2] * 0x10000 + start[3] * 0x1000000);
                d = c;
                c >>= 0x1D;
                d <<= 0x03;
                c |= d;
                start[0] = (char)(c % 0x100);
                c /= 0x100;
                start[1] = (char)(c % 0x100);
                c /= 0x100;
                start[2] = (char)(c % 0x100);
                start[3] = (char)(c / 0x100);
            }

            static unsigned char* MultiplyBytes(unsigned char* input, int count, int mult)
            {
                unsigned char* retVal = new unsigned char[count * mult];
                for (int x = 0; x < count * mult; x++)
                {
                    retVal[x] = input[x % count];
                }
                return retVal;
            }

		public:
			MapleAES(unsigned char* iv, short mapleVersion) {
				m_IV = iv;
				m_MapleVersion = (short)(((mapleVersion >> 8) & 0xFF) | ((mapleVersion << 8) & 0xFF00));
			}

            unsigned char* GetIV()
            {
                return m_IV;
            }

            void UpdateIV()
            {
                m_IV = GetNewIV(m_IV);
            }

            static unsigned char* GetNewIV(unsigned char* _oldIv)
            {
                unsigned char* start = new unsigned char[4]{ 0xf2, 0x53, 0x50, 0xc6 };
                for (int i = 0; i < 4; ++i)
                {
                    Shuffle(_oldIv[i], start);
                }
                return start;
            }

            // PACKET VERIFICATION
            unsigned char* GetHeaderToClient(int _size)
            {
                unsigned char* header = new unsigned char[4];
                int a = m_IV[3] * 0x100 + m_IV[2];
                a ^= -(m_MapleVersion + 1);
                int b = a ^ _size;
                header[0] = (char)(a % 0x100);
                header[1] = (char)((a - header[0]) / 0x100);
                header[2] = (char)(b ^ 0x100);
                header[3] = (char)((b - header[2]) / 0x100);
                return header;
            }

            unsigned char* GetHeaderToServer(int _size)
            {
                unsigned char* header = new unsigned char[4];
                int a = m_IV[3] * 0x100 + m_IV[2];
                a = a ^ m_MapleVersion;
                int b = a ^ _size;
                header[0] = (char)(a % 0x100);
                header[1] = (char)(a / 0x100);
                header[2] = (char)(b % 0x100);
                header[3] = (char)(b / 0x100);
                return header;
            }

            static int GetPacketLength(int _packetHeader)
            {
                int length = (_packetHeader >> 16) ^ (_packetHeader & 0xFFFF);
                length = ((length << 8) & 0xFF00) | ((length >> 8) & 0xFF);
                return length;
            }

            static unsigned short GetPacketLength(unsigned char* buffer)
            {
                return ((*(unsigned short*)(buffer)) ^ (*(unsigned short*)(buffer + 2)));
            }

            bool CheckPacketToServer(unsigned char* _packet)
            {
                int a = _packet[0] ^ m_IV[2];
                int b = m_MapleVersion;
                int c = _packet[1] ^ m_IV[3];
                int d = m_MapleVersion >> 8;
                return (a == b && c == d);
            }

            // AES ENCRYPTION
            void Crypt(unsigned char* _data, size_t size) {
                unsigned char temp_iv[16];
                size_t pos = 0;
                size_t t_pos = 1456;
                size_t bytes_amount;

                aes_encrypt_ctx cx[1];
                aes_init();

                while (size > pos)
                {
                    memcpy(temp_iv, m_IV, 16);
                    aes_encrypt_key256(Constants::GetTrimmedUserKey(), cx);

                    if (size > (pos + t_pos))
                    {
                        bytes_amount = t_pos;
                    }
                    else
                    {
                        bytes_amount = size - pos;
                    }

                    //aes_ofb_crypt(buffer + pos, buffer + pos, bytes_amount, temp_iv, cx);

                    pos += t_pos;
                    t_pos = 1460;
                }
            }

            void Crypt(unsigned char* _data, unsigned int size) {
                int remaining = size;
                int llength = 0x5B0;
                int start = 0;

                aes_encrypt_ctx ctx;

                while (remaining > 0) {
                    unsigned char* myIv = MultiplyBytes(m_IV, 4, 4);

                    if (remaining < llength) {
                        llength = remaining;
                    }

                    for (int x = start; x < (start + llength); x++) {
                        if ((x - start) % 16 == 0) {
                            unsigned char newIv[16];
                            aes_encrypt(myIv, newIv, &ctx);
                            std::memcpy(myIv, newIv, 16);
                        }
                        _data[x] ^= myIv[(x - start) % 16];
                    }

                    start += llength;
                    remaining -= llength;
                    llength = 0x5B4;
                }

                UpdateIV();
                //unsigned char temp_iv[16];
                //unsigned short pos = 0;
                //unsigned short t_pos = 1456;
                //unsigned short bytes_amount;

                //aes_encrypt_ctx cx[1];
                //aes_init();

                //while (size > pos) {
                //    memcpy(temp_iv, m_IV.data(), 16);
                //    aes_encrypt_key256(Constants::GetTrimmedUserKey().data(), cx);

                //    if (size > (pos + t_pos))
                //        bytes_amount = t_pos;
                //    else
                //        bytes_amount = size - pos;

                //    aes_ofb_crypt(_data + pos, _data + pos, bytes_amount, temp_iv, cx);

                //    pos += t_pos;
                //    t_pos = 1460;
                //}
            }
		};
	}
}