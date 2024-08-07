#pragma once

#include <memory>

#include "asio.hpp"


#include "util/LoggingTool.h"
#include "util/ThreadSafeQueue.h"
#include "Typedefs.h"

namespace net
{
    class TCPServerInterface;

    using asio::ip::tcp;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection>
    {
    public:
        TCPConnection(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets);
        ~TCPConnection();

        void connect(TCPServerInterface* server, u32 uid = 0);
        void disconnect();
        bool isConnected();

        void send(const Packet& packet);
        virtual void processPacket(Packet& packet) = 0;

        inline const tcp::socket& getSocket() const { return m_socket; }
        inline const std::string  getIp()     const { return m_socket.remote_endpoint().address().to_string(); }
        inline const Packet&      getIvRecv() const { return m_ivRecv; }
        inline const Packet&      getIvSend() const { return m_ivSend; }

    private:
        void readPacket();
        void readHeaderHandler(const std::error_code& ec, std::size_t bytes_transferred);
        void readBodyHandler(const std::error_code& ec, std::size_t bytes_transferred);
        
        void writePacket();
        void writeHandler(const std::error_code& ec, std::size_t bytes_transferred);

    protected:
        Packet                        m_ivRecv;
        Packet                        m_ivSend;
        util::ThreadSafeQueue<Packet> m_incomingPacketPersonalQueue;  // Holds messages coming from the remote connection(s)
        bool                          m_processingPackets = false;

    private:
        tcp::socket                    m_socket;                    // Unique socket to remote connection
        std::shared_ptr<Packet>        m_tempIncomingPacket;        // Incoming messages are async so we store the partially assembled message here
        util::ThreadSafeQueue<Packet>& m_incomingPacketServerQueue; // Holds messages coming from the remote connection(s)
        util::ThreadSafeQueue<Packet>  m_outgoingPacketQueue;       // Holds messages to be sent to the remote connection
    };
}