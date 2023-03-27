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
        TCPServer(boost::asio::io_context& _ioContext, int _port) : ioContext(_ioContext), acceptor(_ioContext, tcp::endpoint(tcp::v4(), _port)) 
        {
            this->connections = std::make_shared<std::vector<Connection>>();
        }
            
        // Destructor
        virtual ~TCPServer() 
        {
            this->shutdown();
        }
        
        /****************
         * Server functions
         ***************/
        void startAccept() {}

        void shutdown()
        {
            for(Connection c: *(this->connections))
            {
                c->shutdown();
            }
        }

        void handleAccept(std::shared_ptr<MapleClient> _newConnection, const boost::system::error_code& _error) {}

        /*****************
         * Getters & Setters
         ****************/
        boost::asio::io_context& getIoContext() { return this->ioContext; }
        tcp::acceptor& getAcceptor() { return this->acceptor; }
        Connections& getConnections() { return this->connections; }

    private:
        boost::asio::io_context& ioContext;
        tcp::acceptor acceptor;
        Connections connections;
};