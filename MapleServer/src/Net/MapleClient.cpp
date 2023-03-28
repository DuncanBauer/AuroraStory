#include "MapleClient.h"

#include "Net/MapleCrypto.h"
#include "Net/MapleAES.h"

#include "Util/PacketTool.h"

std::shared_ptr<MapleClient> MapleClient::Create(boost::asio::io_context& _ioContext) 
{ 
    return std::shared_ptr<MapleClient>(new MapleClient(_ioContext)); 
}

MapleClient::MapleClient(boost::asio::io_context& _ioContext) : m_Socket(_ioContext)
{
    unsigned char recvIV[4] = {70, 114, 122,  82};
    unsigned char sendIV[4] = {82,  48, 120, 115};

    this->m_SendCipher.reset(new Net::Crypto::MapleAES(sendIV, (short)(0xFFFF - 83)));
    this->m_RecvCipher.reset(new Net::Crypto::MapleAES(recvIV, (short)83));

    this->m_ReadBuffer.reset(new Util::PacketTool());
    this->m_WriteBuffer.reset(new Util::PacketTool());
}

void MapleClient::Start()
{
    unsigned char* recvIV = this->m_RecvCipher->GetIV();
    unsigned char* sendIV = this->m_SendCipher->GetIV();

    // This is the packet for the v83 MapleStory Global(NA) handshake
    Util::PacketTool tool;
    m_WriteBuffer->write<short>(0x0E); // Size
    m_WriteBuffer->write<short>(83); // Major version
    m_WriteBuffer->write<std::string>("1"); // Minor version
    m_WriteBuffer->write<unsigned char>(49);
    m_WriteBuffer->write<char>(*(char*)recvIV);
    m_WriteBuffer->write<char>(*(char*)sendIV);
    m_WriteBuffer->write<unsigned char>(8); // Locale

    //Util::PacketParser::writeShort(buff, 0x0E);
    //Util::PacketParser::writeShort(buff, 83);
    //Util::PacketParser::writeShort(buff, 1);
    //Util::PacketParser::writeByte(buff, 49);
    //Util::PacketParser::writeByte(buff, recvIV);
    //Util::PacketParser::writeByte(buff, sendIV);
    //Util::PacketParser::writeByte(buff, 8);

    this->Write();
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
    m_ReadBuffer.reset(new Util::PacketTool());

    std::cout << "Read\n";
    boost::asio::async_read(GetSocket(),
                            boost::asio::buffer(m_ReadBuffer->GetBuffer(), 4),
                            boost::bind(&MapleClient::HandleReadHeader,
                                        shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void MapleClient::Write()
{
    // Async write
    std::cout << "Write\n";
    boost::asio::async_write(this->GetSocket(),
                            boost::asio::buffer(m_WriteBuffer->GetBuffer(), m_WriteBuffer->GetLength()),
                            boost::bind(&MapleClient::HandleWrite,
                                        shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void MapleClient::HandleReadHeader(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    std::cout << "handleReadHeader\n";
    // If theres an async error, close the connection
    if (!_error)
    {
        std::cout << "\n_bytes_transferred: " << std::dec << _bytes_transferred << std::hex << '\n';

        short packetLength = Net::Crypto::MapleAES::GetPacketLength(m_ReadBuffer->GetBuffer());
        if (packetLength < 2)
        {
            this->Shutdown();
            return;
        }

        // receive the data
        //m_ReadBuffer.reset();

        std::cout << "Packet Length: " << std::dec << packetLength << std::hex << '\n';
        boost::asio::async_read(GetSocket(),
                                boost::asio::buffer(m_ReadBuffer->GetBuffer(), packetLength),
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
        for (int i = 0; i < _bytes_transferred; ++i)
        {
            std::cout << std::setw(2) << (unsigned int)m_ReadBuffer->GetBuffer()[i] << ' ';
        }
        std::cout << "\n\n";

        this->m_RecvCipher->Crypt(m_ReadBuffer->GetBuffer(), _bytes_transferred);

        for (int i = 0; i < _bytes_transferred; ++i)
        {
            std::cout << std::setw(2) << (unsigned int)m_ReadBuffer->GetBuffer()[i] << ' ';
        }
        std::cout << "\n\n";

        Net::Crypto::MapleDecrypt(m_ReadBuffer->GetBuffer(), _bytes_transferred);

        for (int i = 0; i < _bytes_transferred; ++i)
        {
            std::cout << std::setw(2) << (unsigned int)m_ReadBuffer->GetBuffer()[i] << ' ';
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
        for(int i = 0; i < m_WriteBuffer->GetLength(); ++i)
            std::cout << std::hex << (int)m_WriteBuffer->GetBuffer()[i] << " ";
        std::cout << '\n';
        m_WriteBuffer.reset(new Util::PacketTool());
    }
    else
    {
        std::cout << "MapleClient::handleWrite error: " << _error.message() << '\n';
        this->Shutdown();
    }
}