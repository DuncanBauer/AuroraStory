#include "asio.hpp"


#include "Master.h"
#include "net/login/LoginServer.h"
#include "net/channel/ChannelServer.h"

Master::Master()
{
    m_config = YAML::LoadFile("config.yaml");
    m_settings.gameVersion = m_config["gameVersion"].as<uint16_t>();
    m_settings.worldCount = m_config["worldCount"].as<uint16_t>();
    m_settings.loginServerPort = m_config["loginServerPort"].as<uint16_t>();
    m_settings.channelServerPort = m_config["channelServerPort"].as<uint16_t>();
    m_settings.autoRegisterEnabled = m_config["autoRegisterEnabled"].as<bool>();
    m_settings.picEnabled = m_config["picEnabled"].as<bool>();
    m_settings.pinEnabled = m_config["pinEnabled"].as<bool>();
    m_settings.mongoURI = m_config["mongoURI"].as<std::string>();
    m_settings.mongoDB = m_config["mongoDB"].as<std::string>();

    initialize();
}

Master::~Master()
{
}

void Master::initialize()
{
    m_dbHandler.initialize(m_settings.mongoURI, m_settings.mongoDB);
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
