#pragma once

#include <memory>

#include "asio.hpp"
#include "TCPNet.h"
#include "util/Logger.h"
#include "util/ThreadSafeQueue.h"

namespace net
{
    class TCPServerInterface;

    using asio::ip::tcp;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection>
    {
    public:
        TCPConnection(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets);
        ~TCPConnection();

        void connect(TCPServerInterface* server, uint32_t uid = 0);
        void disconnect();
        bool isConnected();

        void send(const Packet& packet);
        virtual void processPacket(Packet& packet) = 0;

        const tcp::socket& getSocket() const;
        const std::vector<byte>& getIvRecv() const;
        const std::vector<byte>& getIvSend() const;

    private:
        void readPacket();
        void readHeaderHandler(const std::error_code& ec, std::size_t bytes_transferred);
        void readBodyHandler(const std::error_code& ec, std::size_t bytes_transferred);
        
        void writePacket();
        void writeHandler(const std::error_code& ec, std::size_t bytes_transferred);

    protected:
        std::vector<byte> m_ivRecv;
        std::vector<byte> m_ivSend;
        util::ThreadSafeQueue<Packet> m_incomingPacketPersonalQueue;  // Holds messages coming from the remote connection(s)
        bool m_processingPackets = false;

    private:
        tcp::socket m_socket;                             // Unique socket to remote connection
        std::shared_ptr<Packet> m_tempIncomingPacket;     // Incoming messages are async so we store the partially assembled message here
        util::ThreadSafeQueue<Packet>& m_incomingPacketServerQueue;  // Holds messages coming from the remote connection(s)
        util::ThreadSafeQueue<Packet> m_outgoingPacketQueue;  // Holds messages to be sent to the remote connection
    };
}