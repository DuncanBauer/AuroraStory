#pragma once

#include "net/asio/TCPConnection.h"

namespace game
{
    using asio::ip::tcp;

    struct PlayerStats
    {

    };

    class Player : public net::TCPConnection
    {
    public:
        Player(tcp::socket socket, util::ThreadSafeQueue<net::Packet>& incomingPackets);
        ~Player();

        int login(const std::string& username, const std::string& password);
        int logout();
        int changeChannel();

    private:
        PlayerStats baseStats;
        PlayerStats modStats;
    };
}