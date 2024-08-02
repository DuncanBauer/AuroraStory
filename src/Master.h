#pragma once

#include "asio.hpp"

#include "World.h"
#include "net/login/LoginServer.h"
#include "net/packets/PacketHandler.h"
#include "util/MongoDb.h"

struct DbSettings
{
    std::string mongoURI;
    std::string mongoDB;
};

struct EventSettings
{
    bool kerningPQEnabled;
    bool ludibriumPQEnabled;
    bool orbisPQEnabled;
    bool ludibriumMazePQEnabled;
};

struct ServerSettings
{
    std::string serverName;
    u16 gameVersion;
    u16 worldCount;

    u16 loginServerInterval;
    u16 rankingInterval;
    bool guestLoginEnabled;
    bool autoRegisterEnabled;
    bool picEnabled;
    bool pinEnabled;

    DbSettings dbSettings;
    EventSettings eventSettings;
};

class Master
{
public:
    // Delete copy constructor and assignment operator
    Master(const Master&) = delete;
    Master& operator=(const Master&) = delete;
    ~Master();

    // Static method to access the singleton instance
    static Master& getInstance();

    asio::io_context& getIoContext();

    void initialize();
    void run();
    void stop();

    inline ServerSettings& getSettings() { return m_settings; }
    
    std::vector<std::shared_ptr<World>> getWorlds();
    std::shared_ptr<World> getWorld(u32 index);

private:
    Master();

private:
    asio::io_context m_ioContext;
    ServerSettings m_settings;

    std::shared_ptr<LoginServer> m_loginServer;
    std::thread m_loginServerThread;

    std::vector<std::shared_ptr<World>> m_worlds;
};