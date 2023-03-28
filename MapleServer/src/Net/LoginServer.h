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
        void StartAccept()
        {
            // Async accept connection
            std::shared_ptr<MapleClient> newConnection = MapleClient::Create(this->GetIoContext());
            GetAcceptor().async_accept(newConnection->GetSocket(),
                                       boost::bind(&LoginServer::HandleAccept,
                                                   std::dynamic_pointer_cast<LoginServer>(shared_from_this()),
                                                   newConnection,
                                                   boost::asio::placeholders::error));
        }

        void HandleAccept(std::shared_ptr<MapleClient> _newConnection, const boost::system::error_code& _error)
        {
            std::cout << "Accepted client\n";
            // If theres an async error, close the connection
            if (!_error)
            {
                // Push new connection onto our list of connections and start communications
                GetConnections()->push_back(_newConnection);
                _newConnection->Start();

                // Async accept new client
                StartAccept();
            }
            else
            {
                std::cout << _error.message() << '\n';
            }
        }
};