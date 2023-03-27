#pragma once

// Aurora Server
#include <memory>

#include "ASIOCommon.h"
#include "Net/MapleCrypto.h"
#include "Net/MapleAES.h"

#include <memory>

class MapleClient : public std::enable_shared_from_this<MapleClient>
{
    public:
        MapleClient() = delete;
        static std::shared_ptr<MapleClient> create(boost::asio::io_context& _ioContext);

        void start();
        void shutdown();

        void read();
        void write();
        void pushOntoWriteQueue(std::string _str)
        {
            std::lock_guard<std::mutex> lock(this->m);
            this->writeBufferQueue.push(_str);
        }

        tcp::socket& getSocket() { return this->socket; }
        std::mutex& getMutex() { return this->m; }

        bool isSocketActive() { return this->mSocketActive; }
        void setSocketActive(bool _active) { this->mSocketActive = _active; }

        std::unique_ptr<unsigned char>& getReadBuffer() { return this->readBuffer; }
        std::queue<std::string>& getWriteBufferQueue() { return this->writeBufferQueue; }

    private:
        Net::Crypto::MapleAES* recvCipher = nullptr;
        Net::Crypto::MapleAES* sendCipher = nullptr;

        std::unique_ptr<unsigned char> readBuffer;
        std::queue<std::string> writeBufferQueue;

        std::mutex m;
        bool mSocketActive = false;
        tcp::socket socket;

        MapleClient(boost::asio::io_context& _ioContext);

        void handleReadHeader(const boost::system::error_code& _error, size_t _bytes_transferred);
        void handleReadBody(const boost::system::error_code& _error, size_t _bytes_transferred);
        void handleWrite(const boost::system::error_code& _error, size_t _bytes_transferred);
};