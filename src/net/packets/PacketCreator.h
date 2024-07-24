#pragma once

#include "net/asio/TCPNet.h"

namespace net
{
    class PacketCreator
    {
    public:
        unsigned char readByte();
        uint16_t readShort();
        int16_t readSignedShort();
        uint32_t readInt();
        int32_t readSignedInt();
        uint64_t readLong();
        int64_t readSignedLong();
        std::string readString(int length);

        void writeByte(unsigned char data);
        void writeShort(uint16_t data);
        void writeSignedShort(int16_t data);
        void writeInt(uint32_t data);
        void writeSignedInt(int32_t data);
        void writeLong(uint64_t data);
        void writeSignedLong(int64_t data);
        void writeString(std::string data);

    private:
        std::vector<unsigned char> m_packetBuffer;
    };
}