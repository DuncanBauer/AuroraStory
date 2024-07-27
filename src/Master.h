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

public:
    static const inline ServerSettings& getServerSettings() { return m_settings; }
    static const inline std::vector<std::string>& getIpBans() { return m_ipBans; }
    static const inline std::vector<std::string>& getMacBans() { return m_macBans; }

private:
    static inline ServerSettings m_settings;
    static inline std::vector<std::string> m_ipBans;
    static inline std::vector<std::string> m_macBans;
    std::vector<World> m_worlds;
};
