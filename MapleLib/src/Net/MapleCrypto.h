#pragma once

// Project headers
#include "Maple.h"
#include "../Util/BitTool.h"

// C++ headers
#include <string>

// Third party headers
#pragma warning(push)
#pragma warning(disable: 26439)
#pragma warning(disable: 26451)
#pragma warning(disable: 26495)
#include <cryptopp/cryptlib.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#pragma warning(pop)

namespace Net
{
    class AURORA_MAPLE_API PacketParser
    {
        public:
            static inline void writeByte(ByteBuffer* _buffer, ByteBuffer* _data)
            {
                for (int i = 0; i < _data->size(); ++i)
                {
                    writeByte(_buffer, _data->operator[](i));
                }
            }

            static inline void writeByte(ByteBuffer* _buffer, int32_t _data)
            {
                writeByte(_buffer, (byte)_data);
            }

            static inline void writeBool(ByteBuffer* _buffer, bool _data)
            {
                _data ? writeByte(_buffer, 1) : writeByte(_buffer, 0);
            }

            static inline void writeInt(ByteBuffer* _buffer, int32_t _data)
            {
                writeByte(_buffer, (byte)(_data & 0xFF));
                writeByte(_buffer, (byte)((_data >> 8) & 0xFF));
                writeByte(_buffer, (byte)((_data >> 16) & 0xFF));
                writeByte(_buffer, (byte)((_data >> 24) & 0xFF));
            }

            static inline void writeShort(ByteBuffer* _buffer, int16_t _data)
            {
                writeByte(_buffer, (byte)(_data & 0xFF));
                writeByte(_buffer, (byte)((_data >> 8) & 0xFF));
            }

            static inline void writeLongLong(ByteBuffer* _buffer, int64_t _data)
            {
                writeByte(_buffer, (byte)(_data & 0xFF));
                writeByte(_buffer, (byte)((_data >> 8) & 0xFF));
                writeByte(_buffer, (byte)((_data >> 16) & 0xFF));
                writeByte(_buffer, (byte)((_data >> 24) & 0xFF));
                writeByte(_buffer, (byte)((_data >> 32) & 0xFF));
                writeByte(_buffer, (byte)((_data >> 40) & 0xFF));
                writeByte(_buffer, (byte)((_data >> 48) & 0xFF));
                writeByte(_buffer, (byte)((_data >> 56) & 0xFF));
            }
            
            static inline void writePos(ByteBuffer* _buffer, int16_t x, int16_t y)
            {
                writeShort(_buffer, x);
                writeShort(_buffer, y);
            }
            
            static inline void writeAsciiString(ByteBuffer* _buffer, std::string _data)
            {
                for (char c : _data)
                {
                    writeByte(_buffer, c);
                }
            }
            
            static inline void writeMapleAsciiString(ByteBuffer* _buffer, std::string _data)
            {
                writeShort(_buffer, (int16_t)_data.size());
                writeAsciiString(_buffer, _data);
            }
            
            static inline void writeNullTerminatedAsciiString(ByteBuffer* _buffer, std::string _data)
            {
                writeAsciiString(_buffer, _data);
                writeByte(_buffer, 0);
            }
            
            static inline int readInt(ByteBuffer* _buffer)
            {
                byte b1 = readByte(_buffer);
                byte b2 = readByte(_buffer);
                byte b3 = readByte(_buffer);
                byte b4 = readByte(_buffer);

                return (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
            }

            static inline short readShort(ByteBuffer* _buffer)
            {
                byte b1 = readByte(_buffer);
                byte b2 = readByte(_buffer);

                return (b2 << 8) + b1;
            }

            static inline long long readLongLong(ByteBuffer* _buffer)
            {
                long long b1 = readByte(_buffer);
                long long b2 = readByte(_buffer);
                long long b3 = readByte(_buffer);
                long long b4 = readByte(_buffer);
                long long b5 = readByte(_buffer);
                long long b6 = readByte(_buffer);
                long long b7 = readByte(_buffer);
                long long b8 = readByte(_buffer);

                return (b8 << 56) + (b7 << 48) + (b6 << 40) + (b5 << 32) + (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
            }
    
            static inline std::string readString(ByteBuffer* _buffer, int _length)
            {
                std::ostringstream str;
                for (int i = 0; i < _length; ++i)
                {
                    str << readByte(_buffer);
                }
                return str.str();
            }
            
            static inline std::string readMapleString(ByteBuffer* _buffer)
            {
                return readString(_buffer, readShort(_buffer));
            }
            
            static inline ByteBuffer nullTermBytes(ByteBuffer* _buffer)
            {
                ByteBuffer newBuffer = *_buffer;
                newBuffer.push_back('\0');
                return newBuffer;
            }

        private:
            static void writeByte(ByteBuffer* _buffer, byte _data)
            {
                _buffer->push_back(_data);
            }
            static byte readByte(ByteBuffer* _buffer)
            {
                if (_buffer->size() > 0)
                {
                    auto val = _buffer->begin();
                    byte ret = *val;
                    _buffer->erase(val);
                    return ret;
                }

                return NULL;
            }
    };

    namespace Crypto
    {
        class AURORA_MAPLE_API MapleCrypto
        {
            public:
                MapleCrypto(short mapleVersion, ByteBuffer iv, bool cryptFlag)
                {
                    m_IV = iv;
                    m_MapleVersion = (short)(((mapleVersion >> 8) & 0xFF) | ((mapleVersion << 8) & 0xFF00));
                    m_CryptFlag = cryptFlag;
                }
                ~MapleCrypto() {}

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
                void crypt(ByteBuffer _data, int length)
                {
                    int remaining = length;
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
                                MapleCrypto::AesCrypt(m_IV, myIv, m_CryptFlag);
                            }
                            _data[i] ^= myIv[(i - start) % 16];
                        }
                        start += llength;
                        remaining -= llength;
                        llength = 0x5b4;
                    }
                    this->updateIV();
                }
                static std::string AesCrypt(ByteBuffer iv, ByteBuffer data, bool cryptFlag)
                {
                    return AesCrypt(iv, Constants::GetTrimmedUserKey(), data, cryptFlag);
                }

                // MAPLE CUSTOM ENCRYPTION
                template<typename T>
                static void MapleEncrypt(ByteBuffer data, T length)
                {
                    size_t j;
                    byte a;
                    byte c;

                    for (size_t i = 0; i < 3; ++i)
                    {
                        a = 0;
                        for (j = length; j > 0; j--)
                        {
                            c = data[length - j];
                            c = Util::BitTool::RollLeft(c, 3);
                            c = (byte)(c + j);
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
                            c = (byte)(c + j);
                            c ^= a;
                            a = c;
                            c ^= 0x13;
                            c = Util::BitTool::RollRight(c, 3);
                            data[j - 1] = c;
                        }
                    }
                }
                template<typename T>
                static void MapleDecrypt(ByteBuffer data, T length)
                {
                    size_t j;
                    byte a;
                    byte b;
                    byte c;
                    
                    for (size_t i = 0; i < 3; ++i)
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
                            c = (byte)(c - j);
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

            private:
                // Bytewise operations
                static void shuffle(byte inputByte, ByteBuffer start)
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
                static std::string AesCrypt(const ByteBuffer _iv, const ByteBuffer _key, const ByteBuffer data, bool cryptFlag)
                {
                    CryptoPP::AutoSeededRandomPool randPool;
                    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

                    CryptoPP::SecByteBlock key(_key.data(), CryptoPP::AES::MAX_KEYLENGTH);
                    CryptoPP::SecByteBlock iv(_iv.data(), CryptoPP::AES::BLOCKSIZE);

                    randPool.GenerateBlock(key, 32);
                    randPool.GenerateBlock(iv, 16);

                    std::string retVal;
                    try
                    {
                        if (cryptFlag)
                        {
                            CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption e;
                            e.SetKeyWithIV(key, key.size(), iv);
                            CryptoPP::StringSource s(data.data(), true, new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(retVal)));
                        }
                        else
                        {
                            CryptoPP::OFB_Mode<CryptoPP::AES>::Decryption d;
                            d.SetKeyWithIV(key, key.size(), iv);
                            CryptoPP::StringSource s(data.data(), true, new CryptoPP::StreamTransformationFilter(d, new CryptoPP::StringSink(retVal)));
                        }
                    }
                    catch (const CryptoPP::Exception& e)
                    {
                        std::cerr << e.what() << std::endl;
                        exit(1);
                    }
                    return retVal;
                }

            private:
                ByteBuffer m_IV;
                short m_MapleVersion;
                bool m_CryptFlag;
        };
    }
};