#pragma once

#include "net/asio/TCPNet.h"

namespace net
{
    class PacketCreator
    {
    public:
        std::vector<byte> getHandshake(std::vector<byte> iv_recv, std::vector<byte> iv_send);

        byte readByte(std::vector<byte>& packet);
        uint16_t readShort(std::vector<byte>& packet);
        int16_t readSignedShort(std::vector<byte>& packet);
        uint32_t readInt(std::vector<byte>& packet);
        int32_t readSignedInt(std::vector<byte>& packet);
        uint64_t readLong(std::vector<byte>& packet);
        int64_t readSignedLong(std::vector<byte>& packet);
        std::string readString(std::vector<byte>& packet, int length);

        void writeByte(std::vector<byte>& packet, byte data);
        void writeSByte(std::vector<byte>& packet, char data);
        void writeShort(std::vector<byte>& packet, uint16_t data);
        void writeSignedShort(std::vector<byte>& packet, int16_t data);
        void writeInt(std::vector<byte>& packet, uint32_t data);
        void writeSignedInt(std::vector<byte>& packet, int32_t data);
        void writeLong(std::vector<byte>& packet, uint64_t data);
        void writeSignedLong(std::vector<byte>& packet, int64_t data);
        void writeString(std::vector<byte>& packet, std::string data);
    };
}