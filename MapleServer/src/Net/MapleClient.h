#pragma once

// Aurora Server
#include "ASIOCommon.h"
#include "Net/MapleCrypto.h"
#include "Util/PacketTool.h"

#include <memory>

class MapleClient : public std::enable_shared_from_this<MapleClient>
{
    public:
        MapleClient() = delete;
        static std::shared_ptr<MapleClient> Create(boost::asio::io_context& _ioContext);

        void Start();
        void Shutdown();

        void Read();
        void Write();

        tcp::socket& GetSocket() { return this->m_Socket; }
        std::mutex& GetMutex() { return this->m_Mutex; }

        unsigned char* GetReadBuffer() { return this->m_ReadBuffer; }
        unsigned char* GetWriteBuffer() { return this->m_WriteBuffer; }

    private:
        unsigned char* m_RecvIV;
        unsigned char* m_SendIV;

        unsigned char* m_ReadBuffer;
        unsigned char* m_WriteBuffer;

        int m_BufferLength = 100;
        int m_CurrLength = 0;
        int m_ReadPos = 0;

        std::mutex m_Mutex;
        tcp::socket m_Socket;

        MapleClient(boost::asio::io_context& _ioContext);
        void HandleReadHeader(const boost::system::error_code& _error, size_t _bytes_transferred);
        void HandleReadBody(const boost::system::error_code& _error, size_t _bytes_transferred);
        void HandleWrite(const boost::system::error_code& _error, size_t _bytes_transferred);
};