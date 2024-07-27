#pragma once

#include "net/asio/TCPConnection.h"

using asio::ip::tcp;

struct PlayerStats
{

};

class Player : public net::TCPConnection
{
public:
    Player(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets);
    ~Player();

    void processPacket(Packet& packet);

    int login(const std::string& username, const std::string& password);
    int logout();
    int changeChannel();

private:
    PlayerStats baseStats;
};