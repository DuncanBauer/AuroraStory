#ifndef MASTER_H
#define MASTER_H

// Aurora Server
#include "World/World.h"
#include "Net/LoginServer.h"

// C++
#include <memory>
#include <vector>

// 3rd Party
#include <boost/asio.hpp>

// Forward Declarations
class TCPServer;

class Master : public std::enable_shared_from_this<Master>
{
  typedef std::shared_ptr<std::vector<std::shared_ptr<World>>> Worlds;
  public:
    Master();

    void run();
    std::shared_ptr<Master> getPtr() { return shared_from_this(); }

    short getMapleVersion() const { return this->m_MapleVersion; }
    int getWorldCount() const { return this->m_WorldCount; }
    int getMaxPlayers() const { return this->m_MaxPlayers; }
    bool getCanAutoRegister() const { return this->m_CanAutoRegister; }
    bool getIsPICEnabled() const { return this->m_IsPICEnabled; }
    bool getIsPINEnabled() const { return this->m_IsPINEnabled; }

    std::string getMysqlIP() const { return this->m_MysqlIP; }
    int getMysqlPort() const { return this->m_MysqlPort; }
    std::string getMysqlUser() const { return this->m_MysqlUser; }
    std::string getMysqlPass() const { return this->m_MysqlPass; }
    std::string getMysqlSchema() const { return this->m_MysqlSchema; }

    std::shared_ptr<LoginServer> getLoginServer() const { return this->pm_Server; }
    int getLoginServerPort() const { return this->m_LoginServerPort; }
    int getChannelServerPort() const { return this->m_ChannelServerPort; }
    int getChannelsPerWorld() const { return this->m_ChannelsPerWorld; }

    Worlds getWorlds() const { return this->worlds; }

  private:
    // SERVER DATA
    short m_MapleVersion;
    int m_WorldCount;
    int m_MaxPlayers;
    bool m_CanAutoRegister;
    bool m_IsPICEnabled;
    bool m_IsPINEnabled;

    // MYSQL DATA
    std::string m_MysqlIP;
    int m_MysqlPort;
    std::string m_MysqlUser;
    std::string m_MysqlPass;
    std::string m_MysqlSchema;

    // LOGIN SERVER DATA
    std::shared_ptr<LoginServer> pm_Server;
    int m_LoginServerPort;
    int m_ChannelServerPort;
    int m_ChannelsPerWorld;

    Worlds worlds;
};

#endif