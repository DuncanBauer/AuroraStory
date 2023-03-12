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

#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

// Aurora Server
#include "ASIOCommon.h"
#include "PacketParser.h"

// C++
#include <memory>

class TCPConnection : public std::enable_shared_from_this<TCPConnection>
{
    public:
        /*****************
         * Constructors
         ****************/
        // Default constructor
        TCPConnection() = delete;

        // Deconstructor
        virtual ~TCPConnection() {};

        static std::shared_ptr<TCPConnection> create(boost::asio::io_context& _ioContext) { return std::shared_ptr<TCPConnection>(new TCPConnection(_ioContext)); }

        /*****************
         * Server Functions
         ****************/
        void start()
        {
            // char recvIV[4] = { 70, 114, 122, 127 };
            // char sendIV[4] = { 82, 48, 120, 127 };
        
            // // This is the packet for the v83 MapleStory Global(NA) handshake
            // ByteBuffer buff;
            // buff.push_back(14);
            // buff.push_back(0);
            // buff.push_back(83);
            // buff.push_back(0);
            // buff.push_back(1);
            // buff.push_back(0);
            // buff.push_back(49);
            // for(int i = 0; i < 4; ++i) { buff.push_back(recvIV[i]); }
            // for(int i = 0; i < 4; ++i) { buff.push_back(sendIV[i]); }
            // buff.push_back(8);

            // this->writeBufferQueue.push(std::string(buff.begin(), buff.end()));
            // this->write();
            // this->read();
        }

        void shutdown()
        {
            // Handles and ignores
            // `The I/O operation has been aborted because of either a thread exit or an application request` exception
            // for a quick and dirty shutdown
            try
            {
                // Shutdown read/write and the socket itself
                this->socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                this->socket.close();
                this->mSocketActive = false;
            }
            catch(std::exception _error)
            {
                std::cout << "TCPConnection::shutdown error: " << _error.what() << '\n';
            }
        }

        size_t completionCondition(const boost::system::error_code& _error, size_t _bytes_transferred)
        {
            if(!_error)
            {
                if(_bytes_transferred >= 2)
                {
                    return 0;
                }
                return -1;
            }
            return 0;
        }

        void read()
        {
            // boost::asio::async_read(this->socket,
            //                         this->readBuffer,
            //                         boost::bind(&TCPConnection::completionCondition,
            //                                     shared_from_this(),
            //                                     boost::asio::placeholders::error,
            //                                     boost::asio::placeholders::bytes_transferred),
            //                         boost::bind(&TCPConnection::handleRead,
            //                                     shared_from_this(),
            //                                     boost::asio::placeholders::error,
            //                                     boost::asio::placeholders::bytes_transferred));
        }

        void write()
        {
            // // Async write
            // if(this->writeBufferQueue.size() > 0 && this->mSocketActive)
            // {
            //     boost::asio::async_write(this->socket,
            //                              boost::asio::buffer(this->writeBufferQueue.front()),
            //                              boost::bind(&TCPConnection::handleWrite,
            //                                          shared_from_this(),
            //                                          boost::asio::placeholders::error,
            //                                          boost::asio::placeholders::bytes_transferred));
            // }
        }

        void pushOntoWriteQueue(std::string _str)
        {
            std::lock_guard<std::mutex> lock(this->m);
            this->writeBufferQueue.push(_str);
        }

        /*****************
         * Getters & Setters
         ****************/
        tcp::socket& getSocket() { return this->socket; }
        std::mutex& getMutex() { return this->m; }
        
        bool isSocketActive() { return this->mSocketActive; }
        void setSocketActive(bool _active) { this->mSocketActive = _active; }
        
        // byte* getReadBuffer() { return this->readBuffer; }
        boost::asio::streambuf& getReadBuffer() { return this->readBuffer; }
        std::queue<std::string> getWriteBufferQueue() { return this->writeBufferQueue; }


    protected:
        TCPConnection(boost::asio::io_context& _ioContext) : socket(_ioContext) 
        {
            this->mSocketActive = true;
            // this->readBuffer = std::make_shared<boost::asio::streambuf>();
            // this->writeBufferQueue = std::make_shared<std::queue<std::string>>();
        }
        boost::asio::streambuf readBuffer;
        // byte* readBuffer;
        std::queue<std::string> writeBufferQueue;

    private:
        void handleRead(const boost::system::error_code& _error, size_t _bytes_transferred)
        {
            // // If theres an async error, close the connection
            // if (!_error)
            // {
            //     // Construct a std::string from a boost::asio::streambuf
            //     // We might read in extra data past the delimiter (According to Boost docs) so we don't read the whole buffer.
            //     // Only read the number of bytes before the \0 
            //     boost::asio::streambuf::const_buffers_type bufs = this->readBuffer.data();
            //     std::string str(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + _bytes_transferred);

            //     byte* bb = new byte[_bytes_transferred];
            //     auto it = boost::asio::buffers_begin(bufs);
            //     for(int i = 0; i < _bytes_transferred; ++i)
            //     {
            //         bb[i] = (unsigned char)*it;
            //         ++it;
            //     }

            //     byte iv[4] = { 70, 114, 122, 127 };
            //     // byte* decrypted = MapleCrypto::AESEncryption::aesDecrypt(iv, bb);
            //     // MapleCrypto::CustomEncryption::decrypt(decrypted, );

            //     // std::cout << std::dec;
            //     // std::cout << decrypted << '\n';
                
            //     // if(str.length() > 30)
            //     // {
            //     //     short version = PacketParser::readShort(&bb);
            //     //     std::string username = PacketParser::readMapleString(&bb);
            //     //     std::string password = PacketParser::readMapleString(&bb);

            //     //     std::cout << "Version: "  << version << '\n';
            //     //     std::cout << "Username: " << username << '\n';
            //     //     std::cout << "Password: " << password << '\n';
            //     // }

            //     // Process data
            //     std::cout << "Bytes received: ";
            //     std::cout << std::hex;
            //     for(int i = 0; i < _bytes_transferred; ++i)
            //     {
            //         std::cout << (unsigned int)str[i] << ' ';
            //     }
            //     std::cout << "\n\n";

            //     // Clear the read buffer
            //     this->readBuffer.consume(_bytes_transferred);
            //     this->read();
            // }
            // else
            // {
            //     std::cout << "Error: " << _error.message() << '\n';
            //     this->shutdown();
            // }
        }

        void handleWrite(const boost::system::error_code& _error, size_t _bytes_transferred)
        {
            // // If theres an async error, close the connection
            // if (!_error)
            // {
            //     // Pop the written packet from the write buffer
            //     std::string str(this->writeBufferQueue.front());
            //     this->writeBufferQueue.pop();
                
            //     // Keep this for testing/examples
            //     std::cout << "Bytes written: ";
            //     for(int i = 0; i < _bytes_transferred; ++i)
            //     {
            //         std::cout << std::hex << (unsigned int)str[i] << ' ';
            //     }
            //     std::cout << "\n\n";

            //     if(this->writeBufferQueue.size() > 0)
            //     {
            //         this->write();
            //     }
            // }
            // else
            // {
            //     std::cout << "Error: " << _error.message() << '\n';
            //     this->shutdown();
            // }
        }

        std::mutex m;
        bool mSocketActive = false;
        tcp::socket socket;
};

#endif