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
    m_serverSettings.dbSettings.mongoURI                  = config["mongoURI"].as<std::string>();
    m_serverSettings.dbSettings.mongoDB                   = config["mongoDB"].as<std::string>();

    // Server Settings
    m_serverSettings.gameVersion                          = config["gameVersion"].as<u16>();
    m_serverSettings.channelCount                         = config["channelCount"].as<u16>();
    m_serverSettings.maxPlayers                           = config["maxPlayers"].as<u16>();

    // Login Settings
    m_serverSettings.loginServerInterval                  = config["loginServerInterval"].as<u16>();
    m_serverSettings.rankingInterval                      = config["rankingInterval"].as<u16>();
    m_serverSettings.guestLoginEnabled                    = config["guestLoginEnabled"].as<bool>();
    m_serverSettings.autoRegisterEnabled                  = config["autoRegisterEnabled"].as<bool>();
    m_serverSettings.picEnabled                           = config["picEnabled"].as<bool>();
    m_serverSettings.pinEnabled                           = config["pinEnabled"].as<bool>();
    
    // World Settings
    m_serverSettings.serverFlag                           = config["serverFlag"].as<u16>();
    m_serverSettings.serverMessage                        = config["serverMessage"].as<std::string>();
    m_serverSettings.eventMessage                         = config["eventMessage"].as<std::string>();
    
    // Event Settings
    m_serverSettings.eventSettings.kerningPQEnabled       = config["kerningPQEnabled"].as<bool>();
    m_serverSettings.eventSettings.ludibriumPQEnabled     = config["ludibriumPQEnabled"].as<bool>();
    m_serverSettings.eventSettings.orbisPQEnabled         = config["orbisPQEnabled"].as<bool>();
    m_serverSettings.eventSettings.ludibriumMazePQEnabled = config["ludibriumMazePQEnabled"].as<bool>();

    // Rates
    m_serverSettings.rates.expRate                        = config["expRate"].as<u16>();
    m_serverSettings.rates.mesoRate                       = config["mesoRate"].as<u16>();
    m_serverSettings.rates.dropRate                       = config["dropRate"].as<u16>();
    m_serverSettings.rates.partyExpRate                   = config["partyExpRate"].as<u16>();
    m_serverSettings.rates.partyDropRate                  = config["partyDropRate"].as<u16>();
    m_serverSettings.rates.partyMesoRate                  = config["partyMesoRate"].as<u16>();
    m_serverSettings.rates.pqExpRate                      = config["pqExpRate"].as<u16>();
    m_serverSettings.rates.bossExpRate                    = config["bossExpRate"].as<u16>();
    m_serverSettings.rates.bossMesoRate                   = config["bossMesoRate"].as<u16>();
    m_serverSettings.rates.bossDropRate                   = config["bossDropRate"].as<u16>();
    m_serverSettings.rates.questExpRate                   = config["questExpRate"].as<u16>();
    m_serverSettings.rates.questMesoRate                  = config["questMesoRate"].as<u16>();
    m_serverSettings.rates.petExpRate                     = config["petExpRate"].as<u16>();

    initialize();
}

Master::~Master()
{
}

void Master::initialize()
{
    // Initialize Logger
    util::LoggingTool::initialize();

    // Initialize MongoDb
    util::MongoDb::initialize(m_serverSettings.dbSettings.mongoURI, m_serverSettings.dbSettings.mongoDB);

    // Initialize PacketHandlers
    PacketHandler::initialize();
}

void Master::run()
{
    // Set up login server
    m_loginServer = std::make_shared<LoginServer>(m_ioContext);
    m_loginServer->start();
    std::cout << "Hello after loginserver start\n";

    // Set up channel servers
    u16 channelPort = 7575;
    for (u16 i = 0; i < m_serverSettings.channelCount; i++)
    {
        m_channelServers.push_back(std::make_shared<ChannelServer>(m_ioContext, channelPort++));
        m_channelServers[i]->start();
        std::cout << "Hello after channelserver" << i+1 << " start\n";
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