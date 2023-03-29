#include "MapleClient.h"

#include "Net/MapleCrypto.h"
#include "Util/PacketTool.h"

std::shared_ptr<MapleClient> MapleClient::Create(boost::asio::io_context& _ioContext) 
{ 
    return std::shared_ptr<MapleClient>(new MapleClient(_ioContext)); 
}

MapleClient::MapleClient(boost::asio::io_context& _ioContext) : m_Socket(_ioContext)
{
    m_ReadBuffer = new unsigned char[Constants::INCREASE_PACKET_BUFFER_SIZE]();
    m_WriteBuffer = new unsigned char[Constants::INCREASE_PACKET_BUFFER_SIZE]();

    m_RecvIV = new unsigned char[Constants::IV_LENGTH](70, 114, 122, 82);
    m_SendIV = new unsigned char[Constants::IV_LENGTH](82, 48, 120, 115);
}

void MapleClient::Start()
{
    // This is the packet for the v83 MapleStory Global(NA) handshake
    Util::PacketTool packetCreator;
    packetCreator.GetHandshake(m_RecvIV, m_SendIV);

    unsigned char* temp = packetCreator.GetBuffer();
    size_t packetLength = packetCreator.GetLength();

    for (int i = 0; i < packetLength; ++i)
        std::cout << std::hex << (int)temp[i] << " ";
    std::cout << '\n';

    unsigned char* packetBuffer = new unsigned char[packetLength];
    memcpy(packetBuffer, temp, packetLength);
    
    for (int i = 0; i < packetLength; ++i)
        std::cout << std::hex << (int)packetBuffer[i] << " ";
    std::cout << '\n';

    boost::asio::async_write(m_Socket,
                             boost::asio::buffer(packetBuffer, packetLength),
                             std::bind(&MapleClient::HandleWrite,
                                       shared_from_this(), 
                                       std::placeholders::_1, 
                                       std::placeholders::_2));
    this->Read();
}

void MapleClient::Shutdown()
{
    // Handles and ignores
    // `The I/O operation has been aborted because of either a thread exit or an application request` exception
    // for a quick and dirty shutdown
    try
    {
        // Shutdown read/write and the socket itself
        m_Socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        m_Socket.close();
    }
    catch (std::exception _error)
    {
        std::cout << "MapleClient::shutdown error: " << _error.what() << '\n';
    }
}

void MapleClient::Read()
{
    std::cout << "Read\n";
    m_ReadBuffer = new unsigned char[4]();
    boost::asio::async_read(GetSocket(), boost::asio::buffer(m_ReadBuffer, 4),
                            boost::bind(&MapleClient::HandleReadHeader,
                                        shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

//void MapleClient::Write()
//{
//    // Async write
//    std::cout << "Write\n";
//    boost::asio::async_write(this->GetSocket(),
//                            boost::asio::buffer(m_WriteBuffer, m_WriteBuffer),
//                            boost::bind(&MapleClient::HandleWrite,
//                                        shared_from_this(),
//                                        boost::asio::placeholders::error,
//                                        boost::asio::placeholders::bytes_transferred));
//}

void MapleClient::HandleReadHeader(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    std::cout << "handleReadHeader\n";
    // If theres an async error, close the connection
    if (!_error)
    {
        std::cout << "\n_bytes_transferred: " << std::dec << _bytes_transferred << std::hex << '\n';

        short packetLength = Crypto::MapleCrypto::GetPacketLength(m_ReadBuffer);
        if (packetLength < 2)
        {
            this->Shutdown();
            return;
        }

        // receive the data
        //m_ReadBuffer.reset(new unsigned char[packetLength]());
        delete[] m_ReadBuffer;
        m_ReadBuffer = new unsigned char[packetLength]();

        std::cout << "Packet Length: " << std::dec << packetLength << std::hex << '\n';
        boost::asio::async_read(GetSocket(),
                                boost::asio::buffer(m_ReadBuffer, packetLength),
                                boost::bind(&MapleClient::HandleReadBody,
                                            shared_from_this(),
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        std::cout << "MapleClient::handleRead error: " << _error.message() << '\n';
        this->Shutdown();
    }
}

void MapleClient::HandleReadBody(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    std::cout << "handleReadBody\n";
    // If theres an async error, close the connection
    if (!_error)
    {
        // Try decrypting
        unsigned short bytes_amount = static_cast<unsigned short>(_bytes_transferred);

        // Process data
        std::cout << std::hex;
        for (int i = 0; i < bytes_amount; ++i)
        {
            std::cout << std::setw(2) << (unsigned int)m_ReadBuffer[i] << ' ';
        }
        std::cout << "\n\n";

        Crypto::MapleCrypto::MapleDecrypt(m_ReadBuffer, m_RecvIV, bytes_amount);

        for (int i = 0; i < bytes_amount; ++i)
        {
            std::cout << std::setw(2) << (unsigned int)m_ReadBuffer[i] << ' ';
        }
        std::cout << "\n\n";
        std::cout << std::dec;

        this->Read();
    }
    else
    {
        std::cout << "MapleClient::handleRead error: " << _error.message() << '\n';
        this->Shutdown();
    }
}

void MapleClient::HandleWrite(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    // If theres an async error, close the connection
    if (!_error)
    {
        // Clear write buffer
        //for(int i = 0; i < m_WriteBuffer; ++i)
        //    std::cout << std::hex << (int)m_WriteBuffer[i] << " ";
        //std::cout << '\n';
        delete[] m_WriteBuffer;
    }
    else
    {
        std::cout << "MapleClient::handleWrite error: " << _error.message() << '\n';
        this->Shutdown();
    }
}