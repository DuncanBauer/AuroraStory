#pragma once

#include "yaml-cpp/yaml.h"

#include "db/DbHandler.h"
#include "net/world/World.h"

struct ServerSettings
{
    // SERVER SETTINGS
    uint16_t gameVersion;
    uint16_t worldCount;
    uint16_t loginServerPort;
    uint16_t channelServerPort;
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

    YAML::Node getConfig();
    db::DbHandler& getDbHandler();

private:
    YAML::Node m_config;
    db::DbHandler m_dbHandler;
    ServerSettings m_settings;
    std::vector<net::World> m_worlds;
};
