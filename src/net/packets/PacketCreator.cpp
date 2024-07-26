#include "pch.h"

#include "PacketCreator.h"
#include "constants/MapleConstants.h"

namespace net
{
    std::vector<byte> PacketCreator::getHandshake(std::vector<byte> iv_recv, std::vector<byte> iv_send)
    {
        std::vector<byte> packet;

        writeShort(packet, 14);
        writeShort(packet, constant::k_gameVersion);
        writeShort(packet, constant::k_gameMinorVersion);
        writeSByte(packet, 49);
        writeInt(packet, *(int*)iv_recv.data());
        writeInt(packet, *(int*)iv_send.data());
        writeSByte(packet, constant::k_gmsLocale);

        return packet;
    }

    byte PacketCreator::readByte(std::vector<byte>& packet)
    {
        byte result = packet.front();
        packet.erase(packet.begin());
        return result;
    }

    uint16_t PacketCreator::readShort(std::vector<byte>& packet)
    {
        uint16_t r1, r2;
        uint16_t result = 0;

        r1 = readByte(packet);
        r2 = readByte(packet);

        result |= r2 << 8;
        result |= r1;

        return result;
    }

    int16_t PacketCreator::readSignedShort(std::vector<byte>& packet)
    {
        int16_t r1, r2;
        int16_t result = 0;

        r1 = readByte(packet);
        r2 = readByte(packet);

        result |= r2 << 8;
        result |= r1;

        return result;
    }

    uint32_t PacketCreator::readInt(std::vector<byte>& packet)
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

    int32_t PacketCreator::readSignedInt(std::vector<byte>& packet)
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

    uint64_t PacketCreator::readLong(std::vector<byte>& packet)
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

    int64_t PacketCreator::readSignedLong(std::vector<byte>& packet)
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

    std::string PacketCreator::readString(std::vector<byte>& packet, int length)
    {
        std::string data;
        for (int i = 0; i < length; i++)
            data += readByte(packet);
        return data;
    }

    std::string PacketCreator::readMapleString(std::vector<byte>& packet)
    {
        return readString(packet, readShort(packet));
    }

    void PacketCreator::writeByte(std::vector<byte>& packet, byte data)
    {
        packet.push_back(data);
    }

    void PacketCreator::writeSByte(std::vector<byte>& packet, char data)
    {
        packet.push_back(data);
    }

    void PacketCreator::writeShort(std::vector<byte>& packet, uint16_t data)
    {
        writeByte(packet, data & 0xFF);
        writeByte(packet, (data >> 8) & 0xFF);
    }

    void PacketCreator::writeSignedShort(std::vector<byte>& packet, int16_t data)
    {
        writeByte(packet, data & 0xFF);
        writeByte(packet, (data >> 8) & 0xFF);
    }

    void PacketCreator::writeInt(std::vector<byte>& packet, uint32_t data)
    {
        writeByte(packet, data & 0xFF);
        writeByte(packet, (data >> 8) & 0xFF);
        writeByte(packet, (data >> 16) & 0xFF);
        writeByte(packet, (data >> 24) & 0xFF);
    }

    void PacketCreator::writeSignedInt(std::vector<byte>& packet, int32_t data)
    {
        writeByte(packet, data & 0xFF);
        writeByte(packet, (data >> 8) & 0xFF);
        writeByte(packet, (data >> 16) & 0xFF);
        writeByte(packet, (data >> 24) & 0xFF);
    }

    void PacketCreator::writeLong(std::vector<byte>& packet, uint64_t data)
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

    void PacketCreator::writeSignedLong(std::vector<byte>& packet, int64_t data)
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

    void PacketCreator::writeString(std::vector<byte>& packet, std::string data)
    {
        if (data.size())
        {
            writeShort(packet, static_cast<short>(data.size()));
            for (byte c : data)
                writeByte(packet, c);
        }
    }
}