#pragma once

#include <memory>
#include <thread>

#include "net/packets/PacketHandler.h"
#include "net/asio/TCPServerInterface.h"

class Player;

class LoginServer : public net::TCPServerInterface
{
public:
    // Delete copy constructor and assignment operator
    LoginServer(const LoginServer&) = delete;
    LoginServer& operator=(const LoginServer&) = delete;
    ~LoginServer();

    // Static method to access the singleton instance
    static LoginServer& getInstance();

    void addToLoginQueue(std::shared_ptr<Player> player);
    void removeFromLoginQueue(std::shared_ptr<Player>player);

protected:
    void onClientConnect(ClientConnection client) override;
    void onClientDisconnect(ClientConnection client) override;
    void onMessage(Packet& packet) override;

private:
    LoginServer(asio::io_context& io_context);

    void updateLoginQueue();

private:
    //std::vector<std::shared_ptr<Player>> m_loginQueue;
    //std::thread m_loginWorker;
};