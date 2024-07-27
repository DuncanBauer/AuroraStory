#pragma once

#include "yaml-cpp/yaml.h"

#include "net/packets/PacketHandler.h"
#include "game/World.h"

struct ServerSettings
{
    // SERVER SETTINGS
    u16 gameVersion;
    u16 worldCount;
    u16 loginServerPort;
    u16 channelServerPort;
    bool guestLoginEnabled;
    bool autoRegisterEnabled;
    bool picEnabled;
    bool pinEnabled;

    // DB
    std::string mongoURI;
    std::string mongoDB;
};

class Master
{
public:
    Master();
    ~Master();

    void initialize();
    void run();
    void stop();

    static const ServerSettings& getServerSettings();

private:
    ServerSettings m_settings;
    std::vector<World> m_worlds;
};
