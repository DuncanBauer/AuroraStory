#pragma once

#include "asio.hpp"

#include "net/login/LoginServer.h"
#include "net/packets/PacketHandler.h"
#include "provider/wz/WzDataProvider.h"
#include "world/World.h"
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
    std::string   serverName;
    u16           gameVersion;
    u16           worldCount;
    u16           defaultMaxCharactersPerWorld;
    u16           wzFileType;

    u16           loginServerInterval;
    u16           rankingInterval;
    bool          guestLoginEnabled;
    bool          autoRegisterEnabled;
    bool          picEnabled;
    bool          pinEnabled;

    DbSettings    dbSettings;
    EventSettings eventSettings;
};

class Master
{
    using WzProviders = std::map<std::string, std::shared_ptr<Provider::WzDataProvider>>;
    using Worlds      = std::vector<std::shared_ptr<World>>;

public:
    // Delete copy constructor and assignment operator
    Master(const Master&) = delete;
    Master(Master&&)      = delete;
    ~Master();

    Master& operator=(const Master&) = delete;

    // Static method to access the singleton instance
    static Master& getInstance();

    void initialize();
    void run();
    void stop();

    inline asio::io_context&                   getIoContext()      { return m_ioContext; }
    inline ServerSettings&                     getSettings()       { return m_settings; }
    inline WzProviders                         getProviders()      { return m_wzProviders; }

    inline Worlds                              getWorlds()         { return m_worlds; }
    inline std::shared_ptr<World>              getWorld(u32 index) { return m_worlds[index]; }

    // DB Interactions
    void createCharacter(u32 accountId, Character character);
    void deleteCharacter(u32 accountId, u32 characterId);

private:
    Master();

private:
    asio::io_context             m_ioContext;
    ServerSettings               m_settings;
    WzProviders                  m_wzProviders;

    std::shared_ptr<LoginServer> m_loginServer;
    std::thread                  m_loginServerThread;

    Worlds                       m_worlds;
};