#pragma once

// Aurora Server
#include "ASIOCommon.h"
#include "TCPServer.h"
#include "MapleClient.h"

class LoginServer : public TCPServer
{
    public:
        /*****************
         * Constructors
         ****************/
        // Default constructor
        LoginServer() = delete;

        // Parameterized constructors
        LoginServer(boost::asio::io_context& _ioContext, int _port) : TCPServer(_ioContext, _port) {}
            
        // Destructor
        ~LoginServer() {}
        
        /****************
         * Server functions
         ***************/
        void startAccept()
        {
            // Async accept connection
            std::shared_ptr<MapleClient> newConnection = std::dynamic_pointer_cast<MapleClient>(MapleClient::create(this->getIoContext()));
            this->getAcceptor().async_accept(newConnection->getSocket(),
                                             boost::bind(&LoginServer::handleAccept,
                                             std::dynamic_pointer_cast<LoginServer>(shared_from_this()),
                                                         newConnection,
                                                         boost::asio::placeholders::error));
        }

        void handleAccept(std::shared_ptr<MapleClient> _newConnection, const boost::system::error_code& _error)
        {
            std::cout << "Accepted client\n";
            // If theres an async error, close the connection
            if (!_error)
            {
                // Push new connection onto our list of connections and start communications
                this->getConnections()->push_back(_newConnection);
                std::dynamic_pointer_cast<MapleClient>(_newConnection)->start();

                // Async accept new client
                this->startAccept();
            }
            else
            {
                std::cout << _error.message() << '\n';
            }
        }
};