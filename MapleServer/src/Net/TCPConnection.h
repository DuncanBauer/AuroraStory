#pragma once

// Aurora Server
#include "ASIOCommon.h"
#include "Util/PacketTool.h"

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
        void start() {}

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

        void read() {}
        void write() {}
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
        
        boost::asio::streambuf& getReadBuffer() { return this->readBuffer; }
        std::queue<std::string> getWriteBufferQueue() { return this->writeBufferQueue; }


    protected:
        TCPConnection(boost::asio::io_context& _ioContext) : socket(_ioContext) {}
        boost::asio::streambuf readBuffer;
        std::queue<std::string> writeBufferQueue;

    private:
        void handleRead(const boost::system::error_code& _error, size_t _bytes_transferred) {}
        void handleWrite(const boost::system::error_code& _error, size_t _bytes_transferred) {}

        std::mutex m;
        bool mSocketActive = false;
        tcp::socket socket;
};