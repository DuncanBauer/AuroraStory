#pragma once

#include "net/asio/TCPNet.h"

namespace net
{
    class PacketCreator
    {
    public:
        static std::vector<byte> getHandshake(std::vector<byte> iv_recv, std::vector<byte> iv_send);

        static byte readByte(std::vector<byte>& packet);
        static uint16_t readShort(std::vector<byte>& packet);
        static int16_t readSignedShort(std::vector<byte>& packet);
        static uint32_t readInt(std::vector<byte>& packet);
        static int32_t readSignedInt(std::vector<byte>& packet);
        static uint64_t readLong(std::vector<byte>& packet);
        static int64_t readSignedLong(std::vector<byte>& packet);
        static std::string readString(std::vector<byte>& packet, int length);
        static std::string readMapleString(std::vector<byte>& packet);

        static void writeByte(std::vector<byte>& packet, byte data);
        static void writeSByte(std::vector<byte>& packet, char data);
        static void writeShort(std::vector<byte>& packet, uint16_t data);
        static void writeSignedShort(std::vector<byte>& packet, int16_t data);
        static void writeInt(std::vector<byte>& packet, uint32_t data);
        static void writeSignedInt(std::vector<byte>& packet, int32_t data);
        static void writeLong(std::vector<byte>& packet, uint64_t data);
        static void writeSignedLong(std::vector<byte>& packet, int64_t data);
        static void writeString(std::vector<byte>& packet, std::string data);
    };
}