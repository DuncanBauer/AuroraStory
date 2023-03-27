#include "MapleClient.h"

#include "Net/MapleCrypto.h"
#include "Net/MapleAES.h"

#include "Util/PacketTool.h"

std::shared_ptr<MapleClient> MapleClient::create(boost::asio::io_context& _ioContext) 
{ 
    return std::shared_ptr<MapleClient>(new MapleClient(_ioContext)); 
}

MapleClient::MapleClient(boost::asio::io_context& _ioContext) : socket(_ioContext)
{
    MapleByteBuffer recvIV = { 70, 114, 122,  82 };
    MapleByteBuffer sendIV = { 82,  48, 120, 115 };

    this->sendCipher = new Net::Crypto::MapleAES(sendIV, (short)(0xFFFF - 83));
    this->recvCipher = new Net::Crypto::MapleAES(recvIV, (short)83);

    this->setSocketActive(true);
}

void MapleClient::start()
{
    MapleByteBuffer recvIV = this->recvCipher->getIV();
    MapleByteBuffer sendIV = this->sendCipher->getIV();

    MapleByteBuffer ivRecv = { 70, 114, 122, 82 };
    MapleByteBuffer ivSend = { 82, 48, 120, 115 };

    // This is the packet for the v83 MapleStory Global(NA) handshake
    MapleByteBuffer buff;
    Util::PacketParser::writeShort(buff, 0x0E);
    Util::PacketParser::writeShort(buff, 83);
    Util::PacketParser::writeShort(buff, 1);
    Util::PacketParser::writeByte(buff, 49);
    Util::PacketParser::writeByte(buff, recvIV);
    Util::PacketParser::writeByte(buff, sendIV);
    Util::PacketParser::writeByte(buff, 8);

    this->pushOntoWriteQueue(std::string(buff.begin(), buff.end()));
    this->write();
    this->read();
}

void MapleClient::shutdown()
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
    catch (std::exception _error)
    {
        std::cout << "MapleClient::shutdown error: " << _error.what() << '\n';
    }
}

void MapleClient::read()
{
    readBuffer.reset(new unsigned char[4]());

    std::cout << "Read\n";
    boost::asio::async_read(getSocket(),
        boost::asio::buffer(readBuffer.get(), 4),
        boost::bind(&MapleClient::handleReadHeader,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void MapleClient::write()
{
    // Async write
    std::cout << "Write\n";
    if (this->writeBufferQueue.size() > 0 && this->isSocketActive())
    {
        boost::asio::async_write(this->getSocket(),
            boost::asio::buffer(this->writeBufferQueue.front()),
            boost::bind(&MapleClient::handleWrite,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }
}

void MapleClient::handleReadHeader(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    std::cout << "handleReadHeader\n";
    // If theres an async error, close the connection
    if (!_error)
    {
        std::cout << "\n_bytes_transferred: " << std::dec << _bytes_transferred << std::hex << '\n';

        short packetLength = Net::Crypto::MapleAES::getPacketLength(readBuffer.get());
        if (packetLength < 2)
        {
            this->shutdown();
            return;
        }

        // receive the data
        readBuffer.reset(new unsigned char[packetLength]());

        std::cout << "Packet Length: " << std::dec << packetLength << std::hex << '\n';
        boost::asio::async_read(this->getSocket(),
            boost::asio::buffer(readBuffer.get(), packetLength),
            boost::bind(&MapleClient::handleReadBody,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        std::cout << "MapleClient::handleRead error: " << _error.message() << '\n';
        this->shutdown();
    }
}

void MapleClient::handleReadBody(const boost::system::error_code& _error, size_t _bytes_transferred)
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
            std::cout << std::setw(2) << (unsigned int)readBuffer.get()[i] << ' ';
        }
        std::cout << "\n\n";

        this->recvCipher->crypt(readBuffer.get(), _bytes_transferred);

        for (int i = 0; i < _bytes_transferred; ++i)
        {
            std::cout << std::setw(2) << (unsigned int)readBuffer.get()[i] << ' ';
        }
        std::cout << "\n\n";

        Net::Crypto::MapleDecrypt(readBuffer.get(), _bytes_transferred);

        for (int i = 0; i < _bytes_transferred; ++i)
        {
            std::cout << std::setw(2) << (unsigned int)readBuffer.get()[i] << ' ';
        }
        std::cout << "\n\n";
        std::cout << std::dec;

        // Clear the read buffer
        this->read();
    }
    else
    {
        std::cout << "MapleClient::handleRead error: " << _error.message() << '\n';
        this->shutdown();
    }
}

void MapleClient::handleWrite(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    // If theres an async error, close the connection
    if (!_error)
    {
        // Pop the written packet from the write buffer
        std::string str(this->writeBufferQueue.front());
        this->writeBufferQueue.pop();

        // Keep this for testing/examples
        std::cout << "Bytes written: ";
        for (int i = 0; i < _bytes_transferred; ++i)
        {
            std::cout << std::hex << (unsigned int)str[i] << ' ';
        }
        std::cout << "\n\n";

        if (this->writeBufferQueue.size() > 0)
        {
            this->write();
        }
    }
    else
    {
        std::cout << "MapleClient::handleWrite error: " << _error.message() << '\n';
        this->shutdown();
    }
}