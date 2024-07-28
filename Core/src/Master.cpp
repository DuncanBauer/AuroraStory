#include "asio.hpp"

#include "yaml-cpp/yaml.h"

#include "Master.h"
#include "util/MongoDb.h"

Master::Master()
{
    // Load Server Configuration
    YAML::Node config = YAML::LoadFile("config.yaml");
    
    // Server data
    m_settings.gameVersion         = config["gameVersion"].as<u16>();
    m_settings.worldCount          = config["worldCount"].as<u16>();
    m_settings.loginServerPort     = config["loginServerPort"].as<u16>();
    m_settings.channelServerPort   = config["channelServerPort"].as<u16>();
    m_settings.loginServerInterval = config["loginServerInterval"].as<u16>();
    m_settings.rankingInterval     = config["rankingInterval"].as<u16>();
    m_settings.guestLoginEnabled   = config["guestLoginEnabled"].as<bool>();
    m_settings.autoRegisterEnabled = config["autoRegisterEnabled"].as<bool>();
    m_settings.picEnabled          = config["picEnabled"].as<bool>();
    m_settings.pinEnabled          = config["pinEnabled"].as<bool>();
    
    // MongoDb data
    m_settings.mongoURI            = config["mongoURI"].as<std::string>();
    m_settings.mongoDB             = config["mongoDB"].as<std::string>();

    // World data
    for (const auto& world : config["worlds"]) 
    {
        World newWorld;

        // Settings
        newWorld.getSettings().flag                   = world["flag"].as<u16>();
        newWorld.getSettings().serverMessage          = world["serverMessage"].as<std::string>();
        newWorld.getSettings().eventMessage           = world["eventMessage"].as<std::string>();
        newWorld.getSettings().channelCount           = world["channelCount"].as<u16>();
        newWorld.getSettings().maxPlayers             = world["maxPlayers"].as<u16>();
        newWorld.getSettings().kerningPQEnabled       = world["kerningPQEnabled"].as<bool>();
        newWorld.getSettings().ludibriumPQEnabled     = world["ludibriumPQEnabled"].as<bool>();
        newWorld.getSettings().orbisPQEnabled         = world["orbisPQEnabled"].as<bool>();
        newWorld.getSettings().ludibriumMazePQEnabled = world["ludibriumMazePQEnabled"].as<bool>();

        // Rates
        newWorld.getRates().expRate                   = world["expRate"].as<u16>();
        newWorld.getRates().mesoRate                  = world["mesoRate"].as<u16>();
        newWorld.getRates().dropRate                  = world["dropRate"].as<u16>();
        newWorld.getRates().partyExpRate              = world["partyExpRate"].as<u16>();
        newWorld.getRates().partyDropRate             = world["partyDropRate"].as<u16>();
        newWorld.getRates().partyMesoRate             = world["partyMesoRate"].as<u16>();
        newWorld.getRates().pqExpRate                 = world["pqExpRate"].as<u16>();
        newWorld.getRates().bossExpRate               = world["bossExpRate"].as<u16>();
        newWorld.getRates().bossMesoRate              = world["bossMesoRate"].as<u16>();
        newWorld.getRates().bossDropRate              = world["bossDropRate"].as<u16>();
        newWorld.getRates().questExpRate              = world["questExpRate"].as<u16>();
        newWorld.getRates().questMesoRate             = world["questMesoRate"].as<u16>();
        newWorld.getRates().petExpRate                = world["petExpRate"].as<u16>();

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
    util::LoggingTool::initialize();

    // Initialize MongoDb
    util::MongoDb::initialize(m_settings.mongoURI, m_settings.mongoDB);

    // Initialize PacketHandlers
    PacketHandler::initialize();
}

void Master::run()
{
    asio::io_context io_context;

    //std::thread loginThread([&io_context]() {
        //net::LoginServer loginServer(io_context, 8484);
        //loginServer.start();
        //io_context.run();
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