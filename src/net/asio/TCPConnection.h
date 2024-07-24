#pragma once

#include "asio.hpp"

#include "net/asio/TCPNet.h"
#include "util/Logger.h"
#include "util/ThreadSafeQueue.h"

namespace net
{
    class TCPServerInterface;

    using asio::ip::tcp;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection>
    {
    public:

        TCPConnection(asio::io_context& ioContext, tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets);

        ~TCPConnection();

        uint32_t getID() const;

        // Connect to client
        void connectToClient(TCPServerInterface* server, uint32_t uid = 0);

        // Disconnect from the client
        void disconnect();

        // Check if the connection is still up
        bool isConnected();

        // Send a written packet to the client
        void send(const Packet& packet);

        // Read an incoming packet header
        void readHeader();

        // Read an incoming packet body
        void readBody();

        // Adds incoming packets to the packet queue for processing
        void addToIncomingPacketQueue();

        // Write a packet header
        void writeHeader();

        // Write a packet body
        void writeBody();

    private:
        uint32_t m_id = 0;

        // Unique socket to remote connection
        tcp::socket m_socket;

        // This context is shared with the asio instance
        asio::io_context& m_ioContext;

        // Incoming messages are async so we store the partially assembled message here
        Packet m_tempIncomingPacket;

        // Holds messages coming from the remote connection(s)
        util::ThreadSafeQueue<Packet>& m_incomingPackets;

        // Holds messages to be sent to the remote connection
        util::ThreadSafeQueue<Packet> m_outgoingPackets;
    };
}