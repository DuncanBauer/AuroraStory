#include "LoginServer.h"
#include "Master.h"
#include "game/Player.h"

namespace net
{
    LoginServer::LoginServer(asio::io_context& io_context) 
        : TCPServerInterface(io_context, 8484)
    {
        loginWorker = std::thread(&LoginServer::updateLoginQueue, this);
    }

    LoginServer::~LoginServer()
    {}

    void LoginServer::addToLoginQueue(std::shared_ptr<Player> player)
    {
        if (player->isGM())
        {
            m_loginQueue.emplace(m_loginQueue.begin(), player);
        }
        else
        {
            m_loginQueue.push_back(player);
        }
    }

    void LoginServer::removeFromLoginQueue(std::shared_ptr<Player> player)
    {
        auto it = std::find(m_loginQueue.begin(), m_loginQueue.end(), player);
        if (it != m_loginQueue.end())
        {
            m_loginQueue.erase(it);
        }
    }

    void LoginServer::onClientConnect(ClientConnection client)
    {

    }

    void LoginServer::onClientDisconnect(ClientConnection client)
    {

    }

    void LoginServer::onMessage(Packet& packet)
    {

    }

    void LoginServer::updateLoginQueue()
    {
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(Master::getServerSettings().loginServerInterval));
        
            
        }
    }
}