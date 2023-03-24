#pragma once

#include "Maple.h"

#include <sstream>
#include <string>

namespace Util {
    namespace PacketParser {
        namespace {
            void writeByte(ByteBuffer& _buffer, const byte _data) {
                _buffer.push_back(_data);
            }

            byte readByte(ByteBuffer& _buffer) {
                if (_buffer.size() > 0)
                {
                    auto val = _buffer.begin();
                    byte ret = *val;
                    _buffer.erase(val);
                    return ret;
                }

                return NULL;
            }
        }

        inline void writeByte(ByteBuffer& _buffer, const ByteBuffer _data) {
            for (int i = 0; i < _data.size(); ++i)
            {
                writeByte(_buffer, _data.operator[](i));
            }
        }

        inline void writeByte(ByteBuffer& _buffer, const int32_t _data) {
            writeByte(_buffer, (byte)_data);
        }

        inline void writeBool(ByteBuffer& _buffer, const bool _data) {
            _data ? writeByte(_buffer, 1) : writeByte(_buffer, 0);
        }

        inline void writeInt(ByteBuffer& _buffer, const int32_t _data) {
            writeByte(_buffer, (byte)(_data & 0xFF));
            writeByte(_buffer, (byte)((_data >> 8) & 0xFF));
            writeByte(_buffer, (byte)((_data >> 16) & 0xFF));
            writeByte(_buffer, (byte)((_data >> 24) & 0xFF));
        }

        inline void writeShort(ByteBuffer& _buffer, const int16_t _data) {
            writeByte(_buffer, (byte)(_data & 0xFF));
            writeByte(_buffer, (byte)((_data >> 8) & 0xFF));
        }

        inline void writeLongLong(ByteBuffer& _buffer, const int64_t _data) {
            writeByte(_buffer, (byte)(_data & 0xFF));
            writeByte(_buffer, (byte)((_data >> 8) & 0xFF));
            writeByte(_buffer, (byte)((_data >> 16) & 0xFF));
            writeByte(_buffer, (byte)((_data >> 24) & 0xFF));
            writeByte(_buffer, (byte)((_data >> 32) & 0xFF));
            writeByte(_buffer, (byte)((_data >> 40) & 0xFF));
            writeByte(_buffer, (byte)((_data >> 48) & 0xFF));
            writeByte(_buffer, (byte)((_data >> 56) & 0xFF));
        }

        inline void writePos(ByteBuffer& _buffer, const size_t x, const size_t y) {
            writeShort(_buffer, x);
            writeShort(_buffer, y);
        }

        inline void writeAsciiString(ByteBuffer& _buffer, const std::string _data) {
            for (char c : _data) {
                writeByte(_buffer, c);
            }
        }

        inline void writeMapleAsciiString(ByteBuffer& _buffer, const std::string _data) {
            writeShort(_buffer, _data.size());
            writeAsciiString(_buffer, _data);
        }

        inline void writeNullTerminatedAsciiString(ByteBuffer& _buffer, const std::string _data) {
            writeAsciiString(_buffer, _data);
            writeByte(_buffer, 0);
        }

        inline int readInt(ByteBuffer& _buffer) {
            byte b1 = readByte(_buffer);
            byte b2 = readByte(_buffer);
            byte b3 = readByte(_buffer);
            byte b4 = readByte(_buffer);

            return (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
        }

        inline short readShort(ByteBuffer& _buffer) {
            byte b1 = readByte(_buffer);
            byte b2 = readByte(_buffer);

            return (b2 << 8) + b1;
        }

        inline long long readLongLong(ByteBuffer& _buffer) {
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

        inline std::string readString(ByteBuffer& _buffer, int _length) {
            std::ostringstream str;
            for (int i = 0; i < _length; ++i)
            {
                str << readByte(_buffer);
            }
            return str.str();
        }

        inline std::string readMapleString(ByteBuffer& _buffer) {
            return readString(_buffer, readShort(_buffer));
        }

        inline ByteBuffer nullTermBytes(ByteBuffer& _buffer) {
            ByteBuffer newBuffer = _buffer;
            newBuffer.push_back('\0');
            return newBuffer;
        }
    };
}