#pragma once

#include <cstdint>
#include <string>

#include "Typedefs.h"

class PacketProcessor
{
public:
    static Packet getHandshake(Packet iv_recv, Packet iv_send);

    static byte readByte(Packet& packet);
    static u16 readShort(Packet& packet);
    static i16 readSignedShort(Packet& packet);
    static u32 readInt(Packet& packet);
    static i32 readSignedInt(Packet& packet);
    static u64 readLong(Packet& packet);
    static int64_t readSignedLong(Packet& packet);
    static std::string readString(Packet& packet, int length);
    static std::string readMapleString(Packet& packet);

    static void writeByte(Packet& packet, byte data);
    static void writeSByte(Packet& packet, char data);
    static void writeShort(Packet& packet, u16 data);
    static void writeSignedShort(Packet& packet, i16 data);
    static void writeInt(Packet& packet, u32 data);
    static void writeSignedInt(Packet& packet, i32 data);
    static void writeLong(Packet& packet, u64 data);
    static void writeSignedLong(Packet& packet, int64_t data);
    static void writeString(Packet& packet, std::string data);
};