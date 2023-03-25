#pragma once

#include "Maple.h"

#include <plusaes/plusaes.hpp>

namespace Net
{
	namespace Crypto
	{
		class AURORA_MAPLE_API MapleAES
		{
		private:
			ByteBuffer m_IV;
			short m_MapleVersion;

        private:
            static void shuffle(byte inputByte, ByteBuffer& start)
            {
                byte a = start[1];
                byte b = a;
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
                start[0] = (byte)(c % 0x100);
                c /= 0x100;
                start[1] = (byte)(c % 0x100);
                c /= 0x100;
                start[2] = (byte)(c % 0x100);
                start[3] = (byte)(c / 0x100);
            }

            static void multiplyBytes(ByteBuffer input, ByteBuffer output, int count, int mult)
            {
                ByteBuffer retVal(count * mult);
                for (int x = 0; x < count * mult; x++)
                {
                    output[x] = input[x % count];
                }
            }

            // AES ENCRYPTION
            //static ByteBuffer AesCrypt(const ByteBuffer _iv, const ByteBuffer _key, const ByteBuffer data, bool cryptFlag)
            static void AesCrypt(const ByteBuffer _iv, const ByteBuffer _key, ByteBuffer& data)
            {
                const unsigned long encrypted_size = plusaes::get_padded_encrypted_size((unsigned long)data.size());
                ByteBuffer encrypted(encrypted_size);

                byte iv[16];
                for (int i = 0; i < _iv.size(); i++) {
                    iv[i] = _iv[i];
                }

                plusaes::encrypt_cbc(data.data(), (unsigned long)data.size(), &_key[0], (unsigned long)_key.size(), &iv, &encrypted[0], (unsigned long)encrypted.size(), false);
                data = encrypted;
            }


		public:
			MapleAES(ByteBuffer iv, short mapleVersion) {
				m_IV = iv;
				m_MapleVersion = (short)(((mapleVersion >> 8) & 0xFF) | ((mapleVersion << 8) & 0xFF00));
			}

            ByteBuffer getIV()
            {
                return m_IV;
            }

            void updateIV()
            {
                m_IV = getNewIV(m_IV);
            }

            static ByteBuffer getNewIV(ByteBuffer _oldIv)
            {
                ByteBuffer start = { 0xf2, 0x53, 0x50, 0xc6 };
                for (int i = 0; i < 4; ++i)
                {
                    shuffle(_oldIv[i], start);
                }
                return start;
            }

            // PACKET VERIFICATION
            ByteBuffer getHeaderToClient(int _size)
            {
                ByteBuffer header(4);
                int a = m_IV[3] * 0x100 + m_IV[2];
                a ^= -(m_MapleVersion + 1);
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
                int a = m_IV[3] * 0x100 + m_IV[2];
                a = a ^ m_MapleVersion;
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

            static unsigned short getPacketLength(ByteBuffer buffer)
            {
                return ((*(unsigned short*)(buffer.data())) ^ (*(unsigned short*)(buffer.data() + 2)));
            }

            bool checkPacketToServer(ByteBuffer _packet)
            {
                int a = _packet[0] ^ m_IV[2];
                int b = m_MapleVersion;
                int c = _packet[1] ^ m_IV[3];
                int d = m_MapleVersion >> 8;
                return (a == b && c == d);
            }

            // AES ENCRYPTION
            void crypt(ByteBuffer& _data)
            {
                int remaining = (int)_data.size();
                int llength = 0x5b0;
                int start = 0;

                while (remaining > 0)
                {
                    ByteBuffer myIv(16);
                    multiplyBytes(m_IV, myIv, 4, 4);
                    if (remaining < llength)
                    {
                        llength = remaining;
                    }

                    for (int i = start; i < start + llength; ++i)
                    {
                        if ((i - start) % 16 == 0)
                        {
                            AesCrypt(m_IV, myIv);
                        }
                        _data[i] ^= myIv[(i - start) % 16];
                    }
                    start += llength;
                    remaining -= llength;
                    llength = 0x5b4;
                }
                this->updateIV();
            }

            static void AesCrypt(ByteBuffer iv, ByteBuffer& data)
            {
                AesCrypt(iv, Constants::GetTrimmedUserKey(), data);
            }
		};
	}
}