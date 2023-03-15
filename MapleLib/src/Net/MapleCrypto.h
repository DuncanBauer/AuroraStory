#pragma once

// Project headers
#include "Maple.h"

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

        namespace Constants
        {
            static const size_t WZ_OFFSET = 0x581C3F6D; // For WZ files

            static const byte WZ_GMS_IV[] = { 0x4D, 0x23, 0xC7, 0x2B }; // For WZ files and game connection i believe. will likely have to search for others. not sure if this once is v83
            static const byte WZ_MSEA_IV[] = { 0x4D, 0x23, 0xC7, 0x2B }; // For WZ files and game connection i believe. will likely have to search for others. not sure if this once is v83
            static const byte DEFAULT_AES_KEY_VALUE[] = {
                0xC6, 0x50, 0x53, 0xF2, 0xA8, 0x42, 0x9D, 0x7F, 0x77, 0x09, 0x1D, 0x26, 0x42, 0x53, 0x88, 0x7C
            };

            static const size_t USER_KEY_LENGTH = 128;
            static const byte DEFAULT_MAPLESTORY_USER_KEY[] = {
                0x13, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x5B, 0x00, 0x00, 0x00,
                0x08, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
                0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00,
                0xB4, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
                0x1B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
                0x0F, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00,
                0x33, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
                0x52, 0x00, 0x00, 0x00, 0xDE, 0x00, 0x00, 0x00, 0xC7, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
            };
            static const byte TRIMMED_DEFAULT_MAPLESTORY_USER_KEY[] = {
                0x13, 0x08, 0x06, 0xB4, 0x1B, 0x0F, 0x33, 0x52
            };

            static ByteBuffer GetTrimmedUserKey()
            {
                ByteBuffer key;
                for (size_t i = 0; i < 128; i += 16)
                {
                    key.push_back(DEFAULT_MAPLESTORY_USER_KEY[i]);
                }
                return key;
            }

            static const byte BYTE_SHUFFLE[] = {
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
                            c = RollLeft(c, 3);
                            c = (byte)(c + j);
                            c ^= a;
                            a = c;
                            c = RollRight(a, j);
                            c ^= 0xFF;
                            c += 0x48;
                            data[length - j] = c;
                        }
                        a = 0;

                        for (j = length; j > 0; --j)
                        {
                            c = data[j - 1];
                            c = RollLeft(c, 4);
                            c = (byte)(c + j);
                            c ^= a;
                            a = c;
                            c ^= 0x13;
                            c = RollRight(c, 3);
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
                            c = RollLeft(c, 3);
                            c ^= 0x13;
                            a = c;
                            c ^= b;
                            c = (byte)(c - j);
                            c = RollRight(c, 4);
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
                            c = RollLeft(c, j);
                            a = c;
                            c ^= b;
                            c = (c - j);
                            c = RollRight(c, 3);
                            b = a;
                            data[length - j] = c;
                        }
                    }
                }

            private:
                // Bitwise operations
                static byte RollLeft(byte val, int num)
                {
                    num &= 7;
                    return static_cast<unsigned char>((val << num) | (val >> (8 - num)));
                }
                static byte RollRight(byte val, int num)
                {
                    num &= 7;
                    return (val >> num) | (val << (8 - num));
                    return static_cast<unsigned char>((val >> num) | (val << (8 - num)));
                }

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
                    std::vector<byte> retVal(count * mult);
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