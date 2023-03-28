#pragma once

// Dependencies
// Aurora Server
#include "ASIOCommon.h"
#include "Net/MapleClient.h"

class TCPServer : public std::enable_shared_from_this<TCPServer>
{
    public:
        /*****************
         * Constructors
         ****************/
        // Default constructor
        TCPServer() = delete;

        // Parameterized constructors
        TCPServer(boost::asio::io_context& _ioContext, int _port) : m_IoContext(_ioContext), m_Acceptor(_ioContext, tcp::endpoint(tcp::v4(), _port)) {
            m_Connections = std::make_shared<std::vector<Connection>>();
        }
            
        // Destructor
        virtual ~TCPServer() {
            this->Shutdown();
        }
        
        /****************
         * Server functions
         ***************/
        void StartAccept() {}

        void Shutdown() {
            for(Connection c: *(this->m_Connections))
            {
                c->Shutdown();
            }
        }

        void HandleAccept(std::shared_ptr<MapleClient> _newConnection, const boost::system::error_code& _error) {}

        /*****************
         * Getters & Setters
         ****************/
        boost::asio::io_context& GetIoContext() { return m_IoContext; }
        tcp::acceptor& GetAcceptor() { return m_Acceptor; }
        Connections& GetConnections() { return m_Connections; }

    private:
        boost::asio::io_context& m_IoContext;
        tcp::acceptor m_Acceptor;
        Connections m_Connections;
};