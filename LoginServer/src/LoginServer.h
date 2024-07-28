#pragma once

#include <memory>
#include <thread>

#include "net/packets/PacketHandler.h"
#include "net/asio/TCPServerInterface.h"

class Player;

namespace net
{
    class LoginServer : public TCPServerInterface
    {
    public:
        LoginServer(asio::io_context& io_context);
        ~LoginServer();

        void addToLoginQueue(std::shared_ptr<Player> player);
        void removeFromLoginQueue(std::shared_ptr<Player>player);

    protected:
        void onClientConnect(ClientConnection client) override;
        void onClientDisconnect(ClientConnection client) override;
        void onMessage(Packet& packet) override;

    private:
        void updateLoginQueue();

    private:
        std::vector<std::shared_ptr<Player>> m_loginQueue;
        std::thread loginWorker;
    };
}