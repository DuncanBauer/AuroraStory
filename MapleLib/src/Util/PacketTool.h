#pragma once

#include "Maple.h"

#include <sstream>
#include <string>

namespace Util {
    class PacketTool {
        private:
            unsigned char* m_Buffer;
            size_t m_BufferLength;
            size_t m_CurrLength;
            size_t m_ReadPos;
            size_t m_IncreasePacketBufferSize = 100;

        public:
            PacketTool() {
                m_BufferLength = 0;
                m_CurrLength = 0;
                m_ReadPos = 0;
                m_Buffer = new unsigned char[m_IncreasePacketBufferSize];
            }

            ~PacketTool() {
                if (m_Buffer) {
                    delete m_Buffer;
                }
            }

            unsigned char* GetBuffer() {
                return m_Buffer;
            }

            size_t GetLength() {
                return m_CurrLength;
            }

            // template function specialisation for writing bytes based on the numeric types
            template<typename T>
            void write(T value)
            {
                // adjust buffer
                if (m_CurrLength + sizeof(T) >= m_BufferLength)
                {
                    unsigned char* temp = (unsigned char*)realloc(m_Buffer, m_BufferLength + m_IncreasePacketBufferSize);
                    if (temp != NULL) {
                        m_Buffer = temp;
                        m_BufferLength += m_IncreasePacketBufferSize;
                    }
                }

                *(T*)(m_Buffer + m_CurrLength) = value;
                m_CurrLength += sizeof(T);
            }

            // template function specialisation for writing bytes based on the type bool
            template<>
            void write<bool>(bool value)
            {
                // adjust buffer
                if (m_CurrLength + sizeof(bool) >= m_BufferLength)
                {
                    unsigned char* temp = (unsigned char*)realloc(m_Buffer, m_BufferLength + m_IncreasePacketBufferSize);
                    if (temp != NULL) {
                        m_Buffer = temp;
                        m_BufferLength += m_IncreasePacketBufferSize;
                    }
                }

                m_Buffer[m_CurrLength] = (value ? 1 : 0);
                ++m_CurrLength;
            }

            // template function specialisation for writing bytes based on the type std::string
            template<>
            void write<std::string>(std::string str)
            {
                size_t len = str.length();

                // adjust buffer
                if (m_CurrLength + len >= m_BufferLength)
                {
                    unsigned char* temp = (unsigned char*)realloc(m_Buffer, m_BufferLength + m_IncreasePacketBufferSize);
                    if (temp != NULL) {
                        m_Buffer = temp;
                        m_BufferLength += m_IncreasePacketBufferSize;
                    }
                }

                write<short>(static_cast<short>(len));

                memcpy(m_Buffer + m_CurrLength, str.c_str(), len);
                m_CurrLength += len;
            }

            // this function template should be used to read bytes based on integer types
            template<typename T>
            T read()
            {
                if (m_CurrLength <= m_ReadPos)
                    return 0;

                if (sizeof(T) > (m_CurrLength - m_ReadPos))
                    return 0;

                T val = *(T*)(m_Buffer + m_ReadPos);
                m_ReadPos += sizeof(T);

                return val;
            }

            // template function specialisation for reading bytes based on the type bool
            template<>
            bool read<bool>()
            {
                return read<signed char>() != 0;
            }

            // template function specialisation for reading bytes based on the type std::string
            template<>
            std::string read<std::string>()
            {
                int len = read<short>();

                if (m_CurrLength <= m_ReadPos)
                    return "";

                if (len > (m_CurrLength - m_ReadPos))
                    return "";

                std::string s((char*)m_Buffer + m_ReadPos, len);
                m_ReadPos += len;

                return s;
            }





        //    void writeByte(const unsigned char _data) {
        //        m_Buffer.push_back(_data);
        //    }

        //    unsigned char readByte() {
        //        if (m_Buffer.size() > 0)
        //        {
        //            auto val = m_Buffer.begin();
        //            unsigned char ret = *val;
        //            m_Buffer.erase(val);
        //            return ret;
        //        }

        //        return NULL;
        //    }

        //    void writeByte(const unsigned char* _data, size_t length) {
        //        for (int i = 0; i < length; ++i)
        //        {
        //            writeByte(m_Buffer, _data.operator[](i));
        //        }
        //    }

        //public:
        //    inline void writeByte(const int32_t _data) {
        //        writeByte(m_Buffer, (byte)_data);
        //    }

        //    inline void writeBool(const bool _data) {
        //        _data ? writeByte(m_Buffer, 1) : writeByte(m_Buffer, 0);
        //    }

        //    inline void writeInt(const int32_t _data) {
        //        writeByte(m_Buffer, (byte)(_data & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 8) & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 16) & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 24) & 0xFF));
        //    }

        //    inline void writeShort(const int16_t _data) {
        //        writeByte(m_Buffer, (byte)(_data & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 8) & 0xFF));
        //    }

        //    inline void writeLongLong(const int64_t _data) {
        //        writeByte(m_Buffer, (byte)(_data & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 8) & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 16) & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 24) & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 32) & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 40) & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 48) & 0xFF));
        //        writeByte(m_Buffer, (byte)((_data >> 56) & 0xFF));
        //    }

        //    inline void writePos(const int x, const int y) {
        //        writeShort(m_Buffer, x);
        //        writeShort(m_Buffer, y);
        //    }

        //    inline void writeAsciiString(const std::string _data) {
        //        for (char c : _data) {
        //            writeByte(m_Buffer, c);
        //        }
        //    }

        //    inline void writeMapleAsciiString(const std::string _data) {
        //        writeShort(m_Buffer, (short)_data.size());
        //        writeAsciiString(m_Buffer, _data);
        //    }

        //    inline void writeNullTerminatedAsciiString(const std::string _data) {
        //        writeAsciiString(m_Buffer, _data);
        //        writeByte(m_Buffer, 0);
        //    }

        //    inline int readInt(unsigned char*& m_Buffer) {
        //        unsigned char b1 = readByte(m_Buffer);
        //        unsigned char b2 = readByte(m_Buffer);
        //        unsigned char b3 = readByte(m_Buffer);
        //        unsigned char b4 = readByte(m_Buffer);

        //        return (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
        //    }

        //    inline short readShort(unsigned char*& m_Buffer) {
        //        unsigned char b1 = readByte(m_Buffer);
        //        unsigned char b2 = readByte(m_Buffer);

        //        return (b2 << 8) + b1;
        //    }

        //    inline long long readLongLong(unsigned char*& m_Buffer) {
        //        long long b1 = readByte(m_Buffer);
        //        long long b2 = readByte(m_Buffer);
        //        long long b3 = readByte(m_Buffer);
        //        long long b4 = readByte(m_Buffer);
        //        long long b5 = readByte(m_Buffer);
        //        long long b6 = readByte(m_Buffer);
        //        long long b7 = readByte(m_Buffer);
        //        long long b8 = readByte(m_Buffer);

        //        return (b8 << 56) + (b7 << 48) + (b6 << 40) + (b5 << 32) + (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
        //    }

        //    inline std::string readString(int _length) {
        //        std::ostringstream str;
        //        for (int i = 0; i < _length; ++i)
        //        {
        //            str << readByte(m_Buffer);
        //        }
        //        return str.str();
        //    }

        //    inline std::string readMapleString(unsigned char*& m_Buffer) {
        //        return readString(m_Buffer, readShort(m_Buffer));
        //    }

        //    inline unsigned char* nullTermBytes(unsigned char*& m_Buffer) {
        //        unsigned char* newBuffer = m_Buffer;
        //        newBuffer.push_back('\0');
        //        return newBuffer;
        //    }
    };
}