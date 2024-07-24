#include "PacketCreator.h"

namespace net
{
    unsigned char PacketCreator::readByte()
    {
        unsigned char result = m_packetBuffer.front();
        m_packetBuffer.erase(m_packetBuffer.begin());
        return result;
    }

    uint16_t PacketCreator::readShort()
    {
        uint16_t r1, r2;
        uint16_t result = 0;

        r1 = readByte();
        r2 = readByte();

        result |= r2 << 8;
        result |= r1;

        return result;
    }

    int16_t PacketCreator::readSignedShort()
    {
        int16_t r1, r2;
        int16_t result = 0;

        r1 = readByte();
        r2 = readByte();

        result |= r2 << 8;
        result |= r1;

        return result;
    }

    uint32_t PacketCreator::readInt()
    {
        uint32_t r1, r2, r3, r4;
        uint32_t result = 0;

        r1 = readByte();
        r2 = readByte();
        r3 = readByte();
        r4 = readByte();

        result |= r4 << 24;
        result |= r3 << 16;
        result |= r2 << 8;
        result |= r1;

        return result;
    }

    int32_t PacketCreator::readSignedInt()
    {
        int32_t r1, r2, r3, r4;
        int32_t result = 0;

        r1 = readByte();
        r2 = readByte();
        r3 = readByte();
        r4 = readByte();

        result |= r4 << 24;
        result |= r3 << 16;
        result |= r2 << 8;
        result |= r1;

        return result;
    }

    uint64_t PacketCreator::readLong()
    {
        uint64_t r1, r2, r3, r4,
            r5, r6, r7, r8;
        uint64_t result = 0;

        r1 = readByte();
        r2 = readByte();
        r3 = readByte();
        r4 = readByte();
        r5 = readByte();
        r6 = readByte();
        r7 = readByte();
        r8 = readByte();

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

    int64_t PacketCreator::readSignedLong()
    {
        int64_t r1, r2, r3, r4,
            r5, r6, r7, r8;
        int64_t result = 0;

        r1 = readByte();
        r2 = readByte();
        r3 = readByte();
        r4 = readByte();
        r5 = readByte();
        r6 = readByte();
        r7 = readByte();
        r8 = readByte();

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

    std::string PacketCreator::readString(int length)
    {
        std::string data;
        for (int i = 0; i < length; i++)
            data += readByte();
        return data;
    }

    void PacketCreator::writeByte(unsigned char data)
    {
        m_packetBuffer.push_back(data);
    }

    void PacketCreator::writeShort(uint16_t data)
    {
        writeByte(data & 0xFF);
        writeByte((data >> 8) & 0xFF);
    }

    void PacketCreator::writeSignedShort(int16_t data)
    {
        writeByte(data & 0xFF);
        writeByte((data >> 8) & 0xFF);
    }

    void PacketCreator::writeInt(uint32_t data)
    {
        writeByte(data & 0xFF);
        writeByte((data >> 8) & 0xFF);
        writeByte((data >> 16) & 0xFF);
        writeByte((data >> 24) & 0xFF);
    }

    void PacketCreator::writeSignedInt(int32_t data)
    {
        writeByte(data & 0xFF);
        writeByte((data >> 8) & 0xFF);
        writeByte((data >> 16) & 0xFF);
        writeByte((data >> 24) & 0xFF);
    }

    void PacketCreator::writeLong(uint64_t data)
    {
        writeByte(data & 0xFF);
        writeByte((data >> 8) & 0xFF);
        writeByte((data >> 16) & 0xFF);
        writeByte((data >> 24) & 0xFF);
        writeByte((data >> 32) & 0xFF);
        writeByte((data >> 40) & 0xFF);
        writeByte((data >> 48) & 0xFF);
        writeByte((data >> 56) & 0xFF);
    }

    void PacketCreator::writeSignedLong(int64_t data)
    {
        writeByte(data & 0xFF);
        writeByte((data >> 8) & 0xFF);
        writeByte((data >> 16) & 0xFF);
        writeByte((data >> 24) & 0xFF);
        writeByte((data >> 32) & 0xFF);
        writeByte((data >> 40) & 0xFF);
        writeByte((data >> 48) & 0xFF);
        writeByte((data >> 56) & 0xFF);
    }

    void PacketCreator::writeString(std::string data)
    {
        writeByte(static_cast<short>(data.size()));
        for (unsigned char c : data)
            writeByte(c);
    }
}