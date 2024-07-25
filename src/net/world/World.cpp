#include "asio.hpp"

#include "World.h"
#include "net/login/LoginServer.h"
#include "net/channel/ChannelServer.h"

namespace net
{
    World::World()
    {
    }

    World::~World() {}

    void World::run()
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

    void World::stop() {}
}