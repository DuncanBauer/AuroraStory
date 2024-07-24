#pragma once

#include <iostream>
#include <vector>

namespace net
{
    // Forward declare the connection
    class TCPConnection;

    typedef unsigned char byte;
    typedef std::shared_ptr<TCPConnection> clientConnection;

    struct Packet
    {
        std::vector<unsigned char> body;

        // returns size of entire message packet in bytes
        size_t size() const
        {
            return body.size();
        }
    };
}