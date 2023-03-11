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

// AuroraServer
#include "World.h"
#include "../Master.h"

// C++
#include <iostream>

World::World()
{

}

World::~World()
{

}

// void World::start(boost::asio::io_context& _ioContext, size_t _port)
// {
//   Utils::Logger::log("STARTING WORLD CHANNELS");
//   std::cin.ignore(1000, '\n');
//   if (this->master == nullptr) { std::cout << "fuck\n"; }
//   else { std::cout << "nice"; }
//   this->master->getChannelsPerWorld();
//   std::cin.ignore(1000, '\n');
//   std::cout << this->master->getChannelsPerWorld() << '\n';
//   Utils::Logger::log("STARTING WORLD CHANNELS");
//   std::cin.ignore(1000, '\n');
//   for (size_t j = 0; j < this->master->getChannelsPerWorld(); ++j)
//   {
//     Utils::Logger::log("STARTING CHANNEL " + (_port + j));
//     std::cin.ignore(1000, '\n');
//     std::shared_ptr<ChannelServer> channelServer = std::make_shared<ChannelServer>(ChannelServer(_ioContext, _port + j, this->getPtr()));
//     std::cin.ignore(1000, '\n');
//     Utils::Logger::error("here");
//     std::shared_ptr<std::thread> channelServerThread = std::make_shared<std::thread>(&ChannelServer::startAccept, channelServer);
//     std::cin.ignore(1000, '\n');
//     Utils::Logger::error("here2");
//     //channelServer->setThread(channelServerThread);
//     //this->channels->push_back(channelServer);
//   }
// }
