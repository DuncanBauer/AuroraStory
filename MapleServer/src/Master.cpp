/*********************************************************************************
* AuroraSource
* Copyright(C) 2021 Duncan Bauer <duncanebauer@gmail.com>
*
* This program is free software : you can redistribute itand /or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.If not, see <http://www.gnu.org/licenses/>.
*********************************************************************************/

// Aurora Server
#include "Master.h"
// #include "Net/TCPServer.hpp"
#include "Net/LoginServer.h"

// C++
#include <exception>
#include <iostream>
#include <thread>

// 3rd Party
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>

Master::Master()
{
    m_MapleVersion = 83;
    m_WorldCount = 1;
    m_MaxPlayers = 500;
    m_CanAutoRegister = false;
    m_IsPICEnabled = false;
    m_IsPINEnabled = false;

    // MYSQL DATA
    m_MysqlIP = "localhost";
    m_MysqlPort = 3306;
    m_MysqlUser = "";
    m_MysqlPass = "";
    m_MysqlSchema = "AuroraStory";

    // LOGIN SERVER DATA
    m_LoginServerPort = 8484;
    m_ChannelServerPort = 7575;
    m_ChannelsPerWorld = 3;


    // Read server config and initialize everything

  //// Get server wide settings
  //this->mapleVersion = std::stoi(this->config.getData()["MAPLE_VERSION"]);
  //this->worldCount = std::stoi(this->config.getData()["WORLD_COUNT"]);
  //this->channelsPerWorld = std::stoi(this->config.getData()["CHANNELS_PER_WORLD"]);
  //this->maxPlayers = std::stoi(this->config.getData()["MAX_PLAYERS"]);

  //this->loginServerPort = std::stoi(this->config.getData()["LOGIN_SERVER_PORT"]);
  //this->channelServerPort = std::stoi(this->config.getData()["CHANNEL_SERVER_PORT"]);

  //this->canAutoRegister = Utils::stob(this->config.getData()["AUTO_REGISTER_ENABLED"]);
  //this->isPICEnabled = Utils::stob(this->config.getData()["PIN_ENABLED"]);
  //this->isPINEnabled = Utils::stob(this->config.getData()["PIC_ENABLED"]);

  //this->server = nullptr;

  //// Get MySQL settings
  //Utils::Logger::log("Loading MySQL Settings");
  //this->mysqlIP = this->config.getData()["MYSQL_IP"];
  //this->mysqlPort = std::stoi(this->config.getData()["MYSQL_PORT"]);
  //this->mysqlUser = this->config.getData()["MYSQL_USER"];
  //this->mysqlPass = this->config.getData()["MYSQL_PASSWORD"];
  //this->mysqlSchema = this->config.getData()["MYSQL_SCHEMA"];

  //// Check for multiple worlds
  //Utils::Logger::log("World Count: " + std::to_string(this->worldCount));
  //if (this->worldCount == 1)
  //{
  //  Utils::Logger::log("Initializing world data");
  //  std::shared_ptr<WorldData> data = std::make_shared<WorldData>(WorldData());

  //  data->expRate = std::stoi(this->config.getData()["EXP_RATE"]);
  //  data->mesoRate = std::stoi(this->config.getData()["MESO_RATE"]);
  //  data->dropRate = std::stoi(this->config.getData()["DROP_RATE"]);

  //  data->pqExpRate = std::stoi(this->config.getData()["PQ_EXP_RATE"]);
  //  data->pqMesoRate = std::stoi(this->config.getData()["PQ_MESO_RATE"]);
  //  data->pqDropRate = std::stoi(this->config.getData()["PQ_DROP_RATE"]);

  //  data->questExpRate = std::stoi(this->config.getData()["QUEST_EXP_RATE"]);
  //  data->questMesoRate = std::stoi(this->config.getData()["QUEST_MESO_RATE"]);
  //  data->questDropRate = std::stoi(this->config.getData()["QUEST_DROP_RATE"]);

  //  data->bossExpRate = std::stoi(this->config.getData()["BOSS_EXP_RATE"]);
  //  data->bossMesoRate = std::stoi(this->config.getData()["BOSS_MESO_RATE"]);
  //  data->bossDropRate = std::stoi(this->config.getData()["BOSS_DROP_RATE"]);

  //  data->petExpRate = std::stoi(this->config.getData()["PET_EXP_RATE"]);

  //  Utils::Logger::log("Setting world data");
  //  std::shared_ptr<World> world = std::make_shared<World>(World(data));

  //  Utils::Logger::log("Initializing world vector");
  //  this->worlds = std::make_shared<std::vector<std::shared_ptr<World>>>();

  //  Utils::Logger::log("Pushing world onto vector");
  //  this->worlds->push_back(world);
  //}
  //else if (this->worldCount > 1)
  //{
  // 
  //  Utils::Logger::log("Initializing world vector");
  //  this->worlds = std::make_shared<std::vector<std::shared_ptr<World>>>();
  //  std::cin.ignore(1000, '\n');
  //  
  //  Utils::Logger::log("Initializing world data");
  //  std::vector<std::shared_ptr<WorldData>> data;
  //  for (size_t i = 0; i < this->worldCount; ++i)
  //  {
  //    data.push_back(std::make_shared<WorldData>());
  //    data[i]->expRate = Utils::stoiv(this->config.getData()["EXP_RATE"])[i];
  //    data[i]->mesoRate = Utils::stoiv(this->config.getData()["MESO_RATE"])[i];
  //    data[i]->dropRate = Utils::stoiv(this->config.getData()["DROP_RATE"])[i];

  //    data[i]->pqExpRate = Utils::stoiv(this->config.getData()["PQ_EXP_RATE"])[i];
  //    data[i]->pqMesoRate = Utils::stoiv(this->config.getData()["PQ_MESO_RATE"])[i];
  //    data[i]->pqDropRate = Utils::stoiv(this->config.getData()["PQ_DROP_RATE"])[i];

  //    data[i]->questExpRate = Utils::stoiv(this->config.getData()["QUEST_EXP_RATE"])[i];
  //    data[i]->questMesoRate = Utils::stoiv(this->config.getData()["QUEST_MESO_RATE"])[i];
  //    data[i]->questDropRate = Utils::stoiv(this->config.getData()["QUEST_DROP_RATE"])[i];

  //    data[i]->bossExpRate = Utils::stoiv(this->config.getData()["BOSS_EXP_RATE"])[i];
  //    data[i]->bossMesoRate = Utils::stoiv(this->config.getData()["BOSS_MESO_RATE"])[i];
  //    data[i]->bossDropRate = Utils::stoiv(this->config.getData()["BOSS_DROP_RATE"])[i];

  //    data[i]->petExpRate = Utils::stoiv(this->config.getData()["PET_EXP_RATE"])[i];

  //    std::shared_ptr<World> _world = std::make_shared<World>(data[i]);
  //    this->worlds->push_back(std::move(_world));
  //  }
  //}
}

void Master::run() 
{
  //try {
  //  Utils::Logger::log("STARTING SERVER");

  //  boost::asio::io_context ioContext;
  //  this->server = std::make_shared<LoginServer>(ioContext, 8484);

  //  // Begin our main loop
  //  auto inputLoopLambda = [&]() {
  //    bool q = false;
  //    char cmd;
  //    
  //    while(!q)
  //    {
  //        std::cout << "Quit: (Q or q)" << '\n';
  //        std::cout << "Enter command: " << '\n' << "> ";
  //        std::cin >> cmd;
  //        switch(cmd)
  //        {
  //            case 'Q':
  //                [[fallthrough]];
  //            case 'q':
  //                q = true;
  //                this->server->shutdown();
  //                ioContext.stop();
  //                break;
  //            default:
  //                break;
  //        }
  //    }
  //  };
  //  std::jthread inputThread(inputLoopLambda);
  //  this->server->startAccept();
  //  ioContext.run();

    // // Check worlds isn't null, and set a reference to Master for each world
    // assert(this->worlds);
    // for(int i = 0; i < this->worlds->size(); ++i)
    // {
    //   this->worlds->at(i)->setMaster(this->getPtr());
    // }


    // // Spin up login server on separate thread
    // this->loginServer = std::make_shared<LoginServer>(ioContext, this->loginServerPort);
    // // this->loginServer->startAccept();
    // std::shared_ptr<std::jthread> loginServerThread = std::make_shared<std::jthread>([&](){ this->loginServer->startAccept(); });
    // ioContext.run();

    // // Spin up channel servers on separate threads each for each channel
    // Utils::Logger::log("STARTING CHANNEL SERVERS");
    // for(size_t i = 0; i < this->worldCount; ++i)
    // {
    //  std::cin.ignore(1000, '\n');
    //  this->worlds->at(i)->start(ioContext, this->channelServerPort + (i * this->channelsPerWorld));
    // }

    // loginServerThread.join();
  //}
  //catch (std::exception& e) {
  //  std::cout << e.what() << '\n';
  //  std::cin.ignore(1000, '\n');
  //}
}