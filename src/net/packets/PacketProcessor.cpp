#include "PacketProcessor.h"

byte PacketProcessor::readByte(Packet& packet)
{
    byte result = packet.front();
    packet.erase(packet.begin());
    return result;
}

u16 PacketProcessor::readShort(Packet& packet)
{
    u16 r1, r2;
    u16 result = 0;

    r1 = readByte(packet);
    r2 = readByte(packet);

    result |= r2 << 8;
    result |= r1;

    return result;
}

i16 PacketProcessor::readSignedShort(Packet& packet)
{
    i16 r1, r2;
    i16 result = 0;

    r1 = readByte(packet);
    r2 = readByte(packet);

    result |= r2 << 8;
    result |= r1;

    return result;
}

u32 PacketProcessor::readInt(Packet& packet)
{
    u32 r1, r2, r3, r4;
    u32 result = 0;

    r1 = readByte(packet);
    r2 = readByte(packet);
    r3 = readByte(packet);
    r4 = readByte(packet);

    result |= r4 << 24;
    result |= r3 << 16;
    result |= r2 << 8;
    result |= r1;

    return result;
}

i32 PacketProcessor::readSignedInt(Packet& packet)
{
    i32 r1, r2, r3, r4;
    i32 result = 0;

    r1 = readByte(packet);
    r2 = readByte(packet);
    r3 = readByte(packet);
    r4 = readByte(packet);

    result |= r4 << 24;
    result |= r3 << 16;
    result |= r2 << 8;
    result |= r1;

    return result;
}

u64 PacketProcessor::readLong(Packet& packet)
{
    u64 r1, r2, r3, r4,
        r5, r6, r7, r8;
    u64 result = 0;

    r1 = readByte(packet);
    r2 = readByte(packet);
    r3 = readByte(packet);
    r4 = readByte(packet);
    r5 = readByte(packet);
    r6 = readByte(packet);
    r7 = readByte(packet);
    r8 = readByte(packet);

    result |= r8 << 56;
    result |= r7 << 48;
    result |= r6 << 40;
    result |= r5 << 32;
    result |= r4 << 24;
    result |= r3 << 16;
    result |= r2 << 8;
    result |= r1;

    return result;
}

int64_t PacketProcessor::readSignedLong(Packet& packet)
{
    int64_t r1, r2, r3, r4,
        r5, r6, r7, r8;
    int64_t result = 0;

    r1 = readByte(packet);
    r2 = readByte(packet);
    r3 = readByte(packet);
    r4 = readByte(packet);
    r5 = readByte(packet);
    r6 = readByte(packet);
    r7 = readByte(packet);
    r8 = readByte(packet);

    result |= r8 << 56;
    result |= r7 << 48;
    result |= r6 << 40;
    result |= r5 << 32;
    result |= r4 << 24;
    result |= r3 << 16;
    result |= r2 << 8;
    result |= r1;

    return result;
}

std::string PacketProcessor::readString(Packet& packet, int length)
{
    std::string data;
    for (int i = 0; i < length; i++)
        data += readByte(packet);
    return data;
}

std::string PacketProcessor::readMapleString(Packet& packet)
{
    u16 length = readShort(packet);
    std::string str = readString(packet, length);
    return str;
}

void PacketProcessor::writeByte(Packet& packet, byte data)
{
    packet.push_back(data);
}

void PacketProcessor::writeSByte(Packet& packet, char data)
{
    packet.push_back(data);
}

void PacketProcessor::writeShort(Packet& packet, u16 data)
{
    writeByte(packet, data & 0xFF);
    writeByte(packet, (data >> 8) & 0xFF);
}

void PacketProcessor::writeSignedShort(Packet& packet, i16 data)
{
    writeByte(packet, data & 0xFF);
    writeByte(packet, (data >> 8) & 0xFF);
}

void PacketProcessor::writeInt(Packet& packet, u32 data)
{
    writeByte(packet, data & 0xFF);
    writeByte(packet, (data >> 8) & 0xFF);
    writeByte(packet, (data >> 16) & 0xFF);
    writeByte(packet, (data >> 24) & 0xFF);
}

void PacketProcessor::writeSignedInt(Packet& packet, i32 data)
{
    writeByte(packet, data & 0xFF);
    writeByte(packet, (data >> 8) & 0xFF);
    writeByte(packet, (data >> 16) & 0xFF);
    writeByte(packet, (data >> 24) & 0xFF);
}

void PacketProcessor::writeLong(Packet& packet, u64 data)
{
    writeByte(packet, data & 0xFF);
    writeByte(packet, (data >> 8) & 0xFF);
    writeByte(packet, (data >> 16) & 0xFF);
    writeByte(packet, (data >> 24) & 0xFF);
    writeByte(packet, (data >> 32) & 0xFF);
    writeByte(packet, (data >> 40) & 0xFF);
    writeByte(packet, (data >> 48) & 0xFF);
    writeByte(packet, (data >> 56) & 0xFF);
}

void PacketProcessor::writeSignedLong(Packet& packet, int64_t data)
{
    writeByte(packet, data & 0xFF);
    writeByte(packet, (data >> 8) & 0xFF);
    writeByte(packet, (data >> 16) & 0xFF);
    writeByte(packet, (data >> 24) & 0xFF);
    writeByte(packet, (data >> 32) & 0xFF);
    writeByte(packet, (data >> 40) & 0xFF);
    writeByte(packet, (data >> 48) & 0xFF);
    writeByte(packet, (data >> 56) & 0xFF);
}

void PacketProcessor::writeString(Packet& packet, std::string data)
{
    if (data.size())
    {
        writeShort(packet, static_cast<short>(data.size()));
        for (byte c : data)
            writeByte(packet, c);
    }
}