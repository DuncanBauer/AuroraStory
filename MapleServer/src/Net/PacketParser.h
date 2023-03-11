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

#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

// Aurora Server

// C++
#include <cstdint>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

using byte = unsigned char;
using ByteBuffer = std::vector<byte>;

namespace PacketParser
{
    namespace 
    {
        void writeByte(ByteBuffer* _buffer, byte _data)
        {
            _buffer->push_back(_data); 
        }

        byte readByte(ByteBuffer* _buffer)
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
    }

    inline void writeByte(ByteBuffer* _buffer, ByteBuffer* _data) 
    {
        for (int i = 0; i < _data->size(); ++i) 
        {
            writeByte(_buffer, _data->operator[](i)); 
        }
    }

    inline void writeByte(ByteBuffer* _buffer, int32_t _data) 
    {
        writeByte(_buffer, (byte)_data); 
    }

    inline void writeBool(ByteBuffer* _buffer, bool _data) 
    {
        _data ? writeByte(_buffer, 1) : writeByte(_buffer, 0); 
    }

    inline void writeInt(ByteBuffer* _buffer, int32_t _data)
    {
        writeByte(_buffer, (byte)(_data & 0xFF));
        writeByte(_buffer, (byte)((_data >> 8) & 0xFF));
        writeByte(_buffer, (byte)((_data >> 16) & 0xFF));
        writeByte(_buffer, (byte)((_data >> 24) & 0xFF));
    }

    inline void writeShort(ByteBuffer* _buffer, int16_t _data)
    {
        writeByte(_buffer, (byte)(_data & 0xFF));
        writeByte(_buffer, (byte)((_data >> 8) & 0xFF));
    }

    inline void writeLongLong(ByteBuffer* _buffer, int64_t _data)
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

    inline void writePos(ByteBuffer* _buffer, size_t x, size_t y) 
    { 
        writeShort(_buffer, x); 
        writeShort(_buffer, y);
    }

    inline void writeAsciiString(ByteBuffer* _buffer, std::string _data) 
    { 
        for (char c : _data) 
        { 
            writeByte(_buffer, c); 
        }
    }

    inline void writeMapleAsciiString(ByteBuffer* _buffer, std::string _data)
    {
        writeShort(_buffer, _data.size());
        writeAsciiString(_buffer, _data);
    }

    inline void writeNullTerminatedAsciiString(ByteBuffer* _buffer, std::string _data)
    {
        writeAsciiString(_buffer, _data);
        writeByte(_buffer, 0);
    }

    inline int readInt(ByteBuffer* _buffer)
    {
        byte b1 = readByte(_buffer);
        byte b2 = readByte(_buffer);
        byte b3 = readByte(_buffer);
        byte b4 = readByte(_buffer);

        return (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
    }

    inline short readShort(ByteBuffer* _buffer)
    {
        byte b1 = readByte(_buffer);
        byte b2 = readByte(_buffer);

        return (b2 << 8) + b1;
    }

    inline long long readLongLong(ByteBuffer* _buffer)
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

    inline std::string readString(ByteBuffer* _buffer, int _length)
    {
        std::ostringstream str;
        for (int i = 0; i < _length; ++i)
        {
            str << readByte(_buffer);
        }
        return str.str();
    }

    inline std::string readMapleString(ByteBuffer* _buffer)
    {
        return readString(_buffer, readShort(_buffer));
    }

    inline ByteBuffer nullTermBytes(ByteBuffer* _buffer)
    {
        ByteBuffer newBuffer = *_buffer;
        newBuffer.push_back('\0');
        return newBuffer;
    }
}

#endif