#ifndef MASTER_H
#define MASTER_H

// Aurora Server
#include "World/World.h"
#include "Net/LoginServer.h"

// C++
#include <memory>
#include <vector>

// Boost
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

    size_t getMapleVersion() const { return this->mapleVersion; }
    size_t getWorldCount() const { return this->worldCount; }
    size_t getMaxPlayers() const { return this->maxPlayers; }
    bool getCanAutoRegister() const { return this->canAutoRegister; }
    bool getIsPICEnabled() const { return this->isPICEnabled; }
    bool getIsPINEnabled() const { return this->isPINEnabled; }

    std::string getMysqlIP() const { return this->mysqlIP; }
    size_t getMysqlPort() const { return this->mysqlPort; }
    std::string getMysqlUser() const { return this->mysqlUser; }
    std::string getMysqlPass() const { return this->mysqlPass; }
    std::string getMysqlSchema() const { return this->mysqlSchema; }

    std::shared_ptr<LoginServer> getLoginServer() const { return this->server; }
    size_t getLoginServerPort() const { return this->loginServerPort; }
    size_t getChannelsPerWorld() const { return this->channelsPerWorld; }
    size_t getChannelServerPort() const { return this->channelServerPort; }

    Worlds getWorlds() const { return this->worlds; }

  private:
    //Utils::Config config;

    // SERVER DATA
    size_t mapleVersion;
    size_t worldCount;
    size_t maxPlayers;
    bool canAutoRegister;
    bool isPICEnabled;
    bool isPINEnabled;

    // MYSQL DATA
    std::string mysqlIP;
    size_t mysqlPort;
    std::string mysqlUser;
    std::string mysqlPass;
    std::string mysqlSchema;

    // LOGIN SERVER DATA
    std::shared_ptr<LoginServer> server;
    size_t loginServerPort;

    size_t channelsPerWorld;
    size_t channelServerPort;

    Worlds worlds;
};

#endif