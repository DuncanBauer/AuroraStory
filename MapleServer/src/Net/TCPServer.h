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

#ifndef TCPSERVER_H
#define TCPSERVER_H

// Dependencies
// Aurora Server
#include "ASIOCommon.h"
#include "TCPConnection.h"

class TCPServer : public std::enable_shared_from_this<TCPServer>
{
    public:
        /*****************
         * Constructors
         ****************/
        // Default constructor
        TCPServer() = delete;

        // Parameterized constructors
        TCPServer(boost::asio::io_context& _ioContext, size_t _port) : ioContext(_ioContext), acceptor(_ioContext, tcp::endpoint(tcp::v4(), _port)) 
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
        void startAccept()
        {
            // // Async accept connection
            // std::shared_ptr<TCPConnection> newConnection = TCPConnection::create(this->ioContext);
            // this->acceptor.async_accept(newConnection->getSocket(),
            //                             boost::bind(&TCPServer::handleAccept,
            //                             shared_from_this(),
            //                             newConnection,
            //                             boost::asio::placeholders::error));
        }

        void shutdown()
        {
            for(Connection c: *(this->connections))
            {
                c->shutdown();
            }
        }

        void handleAccept(std::shared_ptr<TCPConnection> _newConnection, const boost::system::error_code& _error)
        {
            // std::cout << "Accepted client\n";
            // // If theres an async error, close the connection
            // if (!_error)
            // {
            //     // Push new connection onto our list of connections and start communications
            //     this->connections->push_back(_newConnection);
            //     _newConnection->start();

            //     // Async accept new client
            //     this->startAccept();
            // }
            // else
            // {
            //     std::cout << _error.message() << '\n';
            // }
        }

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

#endif