#pragma once

#include "net/TCPNet.h"

namespace net
{
    unsigned char readByte(net::Packet& packet);
    uint16_t readShort(net::Packet& packet);
    int16_t readSignedShort(net::Packet& packet);
    uint32_t readInt(net::Packet& packet);
    int32_t readSignedInt(net::Packet& packet);
    uint64_t readLong(net::Packet& packet);
    int64_t readSignedLong(net::Packet& packet);
    std::string readString(net::Packet& packet, int length);

    void writeByte(net::Packet& packet, unsigned char data);
    void writeShort(net::Packet& packet, uint16_t data);
    void writeSignedShort(net::Packet& packet, int16_t data);
    void writeInt(net::Packet& packet, uint32_t data);
    void writeSignedInt(net::Packet& packet, int32_t data);
    void writeLong(net::Packet& packet, uint64_t data);
    void writeSignedLong(net::Packet& packet, int64_t data);
    void writeString(net::Packet& packet, std::string data);
}