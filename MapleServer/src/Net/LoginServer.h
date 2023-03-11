/*********************************************************************************
* AuroraSource - A C++ MapleStory Server Emulator
* Copyright(C) 2021 Duncan Bauer <duncanebauer@gmail.com>
*
* This program is free software : you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************************/

#ifndef LOGINSERVER_H
#define LOGINSERVER_H

// Dependencies
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
        LoginServer(boost::asio::io_context& _ioContext, size_t _port) : TCPServer(_ioContext, _port) {}
            
        // Destructor
        ~LoginServer() {}
        
        /****************
         * Server functions
         ***************/
        void startAccept()
        {
            // Async accept connection
            std::shared_ptr<TCPConnection> newConnection = std::dynamic_pointer_cast<TCPConnection>(MapleClient::create(this->getIoContext()));
            this->getAcceptor().async_accept(newConnection->getSocket(),
                                             boost::bind(&LoginServer::handleAccept,
                                               std::dynamic_pointer_cast<LoginServer>(shared_from_this()),
                                                         newConnection,
                                                         boost::asio::placeholders::error));
        }

        void handleAccept(std::shared_ptr<TCPConnection> _newConnection, const boost::system::error_code& _error)
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

    private:
        // boost::asio::io_context& ioContext;
        // tcp::acceptor acceptor;
        // Connections connections;
};

#endif