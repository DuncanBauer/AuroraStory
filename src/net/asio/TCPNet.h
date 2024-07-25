#pragma once

#include <iostream>
#include <vector>

namespace net
{
    // Forward declare the connection
    class TCPConnection;

    typedef unsigned char byte;
    typedef std::vector<byte> Packet;
    typedef std::shared_ptr<TCPConnection> clientConnection;
}