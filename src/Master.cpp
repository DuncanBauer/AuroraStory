#include <memory>

#include "yaml-cpp/yaml.h"

#include "Master.h"
#include "net/channel/ChannelServer.h"
#include "net/login/LoginServer.h"
#include "net/packets/PacketHandler.h"
#include "util/MongoDb.h"

Master::Master()
{
    // Load Server Configuration
    YAML::Node config = YAML::LoadFile("config.yaml");
    
    // MongoDb data
    m_settings.dbSettings.mongoURI                  = config["mongoURI"].as<std::string>();
    m_settings.dbSettings.mongoDB                   = config["mongoDB"].as<std::string>();

    // Server Settings
    m_settings.serverName                           = config["serverName"].as<std::string>();
    m_settings.gameVersion                          = config["gameVersion"].as<u16>();
    m_settings.worldCount                           = config["worldCount"].as<u16>();
    m_settings.maxCharactersPerWorld                = config["maxCharactersPerWorld"].as<u16>();
    m_settings.wzFileType                           = config["wzFileType"].as<u16>();

    // Login Settings
    m_settings.loginServerInterval                  = config["loginServerInterval"].as<u16>();
    m_settings.rankingInterval                      = config["rankingInterval"].as<u16>();
    m_settings.guestLoginEnabled                    = config["guestLoginEnabled"].as<bool>();
    m_settings.autoRegisterEnabled                  = config["autoRegisterEnabled"].as<bool>();
    m_settings.picEnabled                           = config["picEnabled"].as<bool>();
    m_settings.pinEnabled                           = config["pinEnabled"].as<bool>();

    // Event Settigns
    m_settings.eventSettings.kerningPQEnabled       = config["kerningPQEnabled"].as<bool>();
    m_settings.eventSettings.ludibriumPQEnabled     = config["ludibriumPQEnabled"].as<bool>();
    m_settings.eventSettings.orbisPQEnabled         = config["orbisPQEnabled"].as<bool>();
    m_settings.eventSettings.ludibriumMazePQEnabled = config["ludibriumMazePQEnabled"].as<bool>();
    
    // Loop through each world in the list
    int i = 0;
    for (const auto& world : config["worlds"]) 
    {
        WorldSettings worldSettings;

        worldSettings.serverFlag                           = world["serverFlag"].as<u16>();
        worldSettings.serverMessage                        = world["serverMessage"].as<std::string>();
        worldSettings.eventMessage                         = world["eventMessage"].as<std::string>();
        worldSettings.channelCount                         = world["channelCount"].as<u16>();
        worldSettings.maxPlayers                           = world["maxPlayers"].as<u16>();

        worldSettings.rates.mesoRate                       = world["mesoRate"].as<u16>();
        worldSettings.rates.dropRate                       = world["dropRate"].as<u16>();
        worldSettings.rates.partyExpRate                   = world["partyExpRate"].as<u16>();
        worldSettings.rates.partyDropRate                  = world["partyDropRate"].as<u16>();
        worldSettings.rates.partyMesoRate                  = world["partyMesoRate"].as<u16>();
        worldSettings.rates.bossExpRate                    = world["bossExpRate"].as<u16>();
        worldSettings.rates.bossMesoRate                   = world["bossMesoRate"].as<u16>();
        worldSettings.rates.bossDropRate                   = world["bossDropRate"].as<u16>();
        worldSettings.rates.questExpRate                   = world["questExpRate"].as<u16>();
        worldSettings.rates.questMesoRate                  = world["questMesoRate"].as<u16>();
        worldSettings.rates.pqExpRate                      = world["pqExpRate"].as<u16>();
        worldSettings.rates.petExpRate                     = world["petExpRate"].as<u16>();

        m_worlds.push_back(std::make_shared<World>(worldSettings));
        if (++i >= m_settings.worldCount)
        {
            break;
        }
    }

    initialize();
}

Master::~Master()
{
}

Master& Master::getInstance()
{
    static Master instance; // Guaranteed to be destroyed
    return instance;
}

asio::io_context& Master::getIoContext()
{
    return m_ioContext;
}

void Master::initialize()
{
    // Initialize Logger
    util::LoggingTool::initialize();

    // Initialize MongoDb
    util::MongoDb::getInstance().initialize(m_settings.dbSettings.mongoURI, m_settings.dbSettings.mongoDB);
    //util::MongoDb::initialize(m_settings.dbSettings.mongoURI, m_settings.dbSettings.mongoDB);

    // Initialize PacketHandlers
    PacketHandler::initialize();
}

void Master::run()
{
    // Set up login server
    LoginServer::getInstance().start();
    //m_loginServerThread = std::thread([this]() { m_loginServer->update(); });

    u16 channelPort = 7575;
    for (std::shared_ptr<World> world : m_worlds)
    {
        world->startChannels(channelPort);
    }

    m_ioContext.run();

    // Begin our main loop
    bool q = false;
    char cmd;

    while (!q)
    {
        std::cin >> cmd;
        switch (cmd)
        {
        case 'Q':
            [[fallthrough]];
        case 'q':
            q = true;
            break;
        default:
            break;
        }
    }
}

void Master::stop()
{}

std::vector<std::shared_ptr<World>> Master::getWorlds()
{
    return m_worlds;
}

std::shared_ptr<World> Master::getWorld(u32 index)
{
    return m_worlds[index];
}