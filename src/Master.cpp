#include "pch.h"

#include "asio.hpp"

#include "Master.h"
#include "net/login/LoginServer.h"
#include "net/channel/ChannelServer.h"

Master::Master()
{
    // Load Server Configuration
    m_config = YAML::LoadFile("config.yaml");
    
    // Server data
    m_settings.gameVersion         = m_config["gameVersion"].as<uint16_t>();
    m_settings.worldCount          = m_config["worldCount"].as<uint16_t>();
    m_settings.loginServerPort     = m_config["loginServerPort"].as<uint16_t>();
    m_settings.channelServerPort   = m_config["channelServerPort"].as<uint16_t>();
    m_settings.guestLoginEnabled   = m_config["guestLoginEnabled"].as<bool>();
    m_settings.autoRegisterEnabled = m_config["autoRegisterEnabled"].as<bool>();
    m_settings.picEnabled          = m_config["picEnabled"].as<bool>();
    m_settings.pinEnabled          = m_config["pinEnabled"].as<bool>();
    
    // MongoDb data
    m_settings.mongoURI            = m_config["mongoURI"].as<std::string>();
    m_settings.mongoDB             = m_config["mongoDB"].as<std::string>();

    // World data
    for (const auto& world : m_config["worlds"]) {
        net::World newWorld;

        // Settings
        newWorld.getSettings().flag                   = world["flag"].as<uint16_t>();
        newWorld.getSettings().serverMessage          = world["serverMessage"].as<std::string>();
        newWorld.getSettings().eventMessage           = world["eventMessage"].as<std::string>();
        newWorld.getSettings().channelCount           = world["channelCount"].as<uint16_t>();
        newWorld.getSettings().maxPlayers             = world["maxPlayers"].as<uint16_t>();
        newWorld.getSettings().kerningPQEnabled       = world["kerningPQEnabled"].as<bool>();
        newWorld.getSettings().ludibriumPQEnabled     = world["ludibriumPQEnabled"].as<bool>();
        newWorld.getSettings().orbisPQEnabled         = world["orbisPQEnabled"].as<bool>();
        newWorld.getSettings().ludibriumMazePQEnabled = world["ludibriumMazePQEnabled"].as<bool>();

        // Rates
        newWorld.getRates().expRate                   = world["expRate"].as<uint16_t>();
        newWorld.getRates().mesoRate                  = world["mesoRate"].as<uint16_t>();
        newWorld.getRates().dropRate                  = world["dropRate"].as<uint16_t>();
        newWorld.getRates().partyExpRate              = world["partyExpRate"].as<uint16_t>();
        newWorld.getRates().partyDropRate             = world["partyDropRate"].as<uint16_t>();
        newWorld.getRates().partyMesoRate             = world["partyMesoRate"].as<uint16_t>();
        newWorld.getRates().pqExpRate                 = world["pqExpRate"].as<uint16_t>();
        newWorld.getRates().bossExpRate               = world["bossExpRate"].as<uint16_t>();
        newWorld.getRates().bossMesoRate              = world["bossMesoRate"].as<uint16_t>();
        newWorld.getRates().bossDropRate              = world["bossDropRate"].as<uint16_t>();
        newWorld.getRates().questExpRate              = world["questExpRate"].as<uint16_t>();
        newWorld.getRates().questMesoRate             = world["questMesoRate"].as<uint16_t>();
        newWorld.getRates().petExpRate                = world["petExpRate"].as<uint16_t>();

        m_worlds.push_back(newWorld);
    }

    initialize();
}

Master::~Master()
{
}

void Master::initialize()
{
    // Initialize Logger
    util::Logger::init();

    // Initialize MongoDb
    m_dbHandler.initialize(m_settings.mongoURI, m_settings.mongoDB);

    // Initialize PacketHandlers
    packetHandler.registerHandlers();
}

void Master::run()
{
    asio::io_context io_context;

    //std::thread loginThread([&io_context]() {
        net::LoginServer loginServer(io_context, 8484);
        loginServer.start();
        io_context.run();
    //});
    //loginThread.detach();

    //std::thread channel1Thread([&io_context]() {
    //    net::ChannelServer channelServer1(io_context, 7575);
    //    channelServer1.start();
    //    io_context.run();
    //});
    //channel1Thread.detach();


    //// Begin our main loop
    //bool q = false;
    //char cmd;

    //while (!q)
    //{
    //    std::cin >> cmd;
    //    switch (cmd)
    //    {
    //    case 'Q':
    //        [[fallthrough]];
    //    case 'q':
    //        q = true;
    //        break;
    //    default:
    //        break;
    //    }
    //}


    //if (loginThread.joinable())
    //    loginThread.join();

    //if (channel1Thread.joinable())
    //    channel1Thread.join();
}

void Master::stop()
{}

YAML::Node Master::getConfig()
{
    return m_config;
}

db::DbHandler& Master::getDbHandler()
{
    return m_dbHandler;
}
