#pragma once

// Aurora Server
#include "ASIOCommon.h"
#include "Net/MapleCrypto.h"
#include "Net/MapleAES.h"
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

        std::unique_ptr<Util::PacketTool>& GetReadBuffer() { return this->m_ReadBuffer; }
        std::unique_ptr<Util::PacketTool>& GetWriteBuffer() { return this->m_WriteBuffer; }

    private:
        std::unique_ptr<Net::Crypto::MapleAES> m_RecvCipher;
        std::unique_ptr<Net::Crypto::MapleAES> m_SendCipher;

        std::unique_ptr<Util::PacketTool> m_ReadBuffer;
        std::unique_ptr<Util::PacketTool> m_WriteBuffer;

        std::mutex m_Mutex;
        tcp::socket m_Socket;

        MapleClient(boost::asio::io_context& _ioContext);
        void HandleReadHeader(const boost::system::error_code& _error, size_t _bytes_transferred);
        void HandleReadBody(const boost::system::error_code& _error, size_t _bytes_transferred);
        void HandleWrite(const boost::system::error_code& _error, size_t _bytes_transferred);
};