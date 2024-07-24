#include "PacketTool.h"

namespace net
{
    unsigned char readByte(net::Packet& packet)
    {
        unsigned char result = packet.body.front();
        packet.body.erase(packet.body.begin());
        packet.header.size--;
        return result;
    }

    uint16_t readShort(net::Packet& packet)
    {
        uint16_t r1, r2;
        uint16_t result = 0;

        r1 = readByte(packet);
        r2 = readByte(packet);

        result |= r2 << 8;
        result |= r1;

        return result;
    }

    int16_t readSignedShort(net::Packet& packet)
    {
        int16_t r1, r2;
        int16_t result = 0;

        r1 = readByte(packet);
        r2 = readByte(packet);

        result |= r2 << 8;
        result |= r1;

        return result;
    }

    uint32_t readInt(net::Packet& packet)
    {
        uint32_t r1, r2, r3, r4;
        uint32_t result = 0;

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

    int32_t readSignedInt(net::Packet& packet)
    {
        int32_t r1, r2, r3, r4;
        int32_t result = 0;

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

    uint64_t readLong(net::Packet& packet)
    {
        uint64_t r1, r2, r3, r4,
            r5, r6, r7, r8;
        uint64_t result = 0;

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

    int64_t readSignedLong(net::Packet& packet)
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

    std::string readString(net::Packet& packet, int length)
    {
        std::string data;
        for (int i = 0; i < length; i++)
            data += readByte(packet);
        return data;
    }

    void writeByte(net::Packet& packet, unsigned char data)
    {
        packet.body.push_back(data);
        packet.header.size++;
    }

    void writeShort(net::Packet& packet, uint16_t data)
    {
        writeByte(packet, data & 0xFF);
        writeByte(packet, (data >> 8) & 0xFF);
    }

    void writeSignedShort(net::Packet& packet, int16_t data)
    {
        writeByte(packet, data & 0xFF);
        writeByte(packet, (data >> 8) & 0xFF);
    }

    void writeInt(net::Packet& packet, uint32_t data)
    {
        writeByte(packet, data & 0xFF);
        writeByte(packet, (data >> 8) & 0xFF);
        writeByte(packet, (data >> 16) & 0xFF);
        writeByte(packet, (data >> 24) & 0xFF);
    }

    void writeSignedInt(net::Packet& packet, int32_t data)
    {
        writeByte(packet, data & 0xFF);
        writeByte(packet, (data >> 8) & 0xFF);
        writeByte(packet, (data >> 16) & 0xFF);
        writeByte(packet, (data >> 24) & 0xFF);
    }

    void writeLong(net::Packet& packet, uint64_t data)
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

    void writeSignedLong(net::Packet& packet, int64_t data)
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

    void writeString(net::Packet& packet, std::string data)
    {
        for (unsigned char c : data)
            writeByte(packet, c);
    }
}