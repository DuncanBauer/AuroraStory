#pragma once

#include <string>

#include "Typedefs.h"

namespace util
{
    namespace PacketTool
    {
        byte              readByte(Packet& packet);
        u16               readShort(Packet& packet);
        u32               readInt(Packet& packet);
        u64               readLong(Packet& packet);
        std::string       readString(Packet& packet, int length);
        std::string       readMapleString(Packet& packet);
        
        void              writeByte(Packet& packet, byte data);
        void              writeShort(Packet& packet, u16 data);
        void              writeInt(Packet& packet, u32 data);
        void              writeIntAsByte(Packet& packet, u32 data);
        void              writeLong(Packet& packet, u64 data);
        void              writeString(Packet& packet, std::string data);
        void              writeMapleString(Packet& packet, std::string data);
        void              writeByteArray(Packet& packet, std::vector<byte> byteArray);

        std::stringstream outputShortHex(short packetShort);
        std::stringstream outputByteHex(byte packetByte);
        //std::stringstream outputPacketHex(Packet packet);
        std::stringstream outputPacketHex(Packet packet);
        std::stringstream outputByteBufferHex(byte* buffer, size_t size);
        std::stringstream outputPacketDec(Packet packet);
        std::stringstream outputPacketString(Packet packet);

    }
}