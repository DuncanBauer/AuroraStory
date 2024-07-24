#pragma once

#include <iostream>
#include <vector>

namespace net
{
    // Forward declare the connection
    class TCPConnection;

    typedef unsigned char byte;
    typedef std::shared_ptr<TCPConnection> clientConnection;

    struct PacketHeader
    {
        byte id;
        size_t size = 0;
    };

    struct Packet
    {
        // Header & Body vector
        PacketHeader header;
        std::vector<unsigned char> body;

        // returns size of entire message packet in bytes
        size_t size() const
        {
            return body.size();
        }
    };

    struct OwnedPacket
    {
        std::shared_ptr<TCPConnection> owner = nullptr;
        Packet packet;
    };
}