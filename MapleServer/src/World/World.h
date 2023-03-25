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

#ifndef WORLD_H
#define WORLD_H

// C++
#include <memory>
#include <vector>

// typedef std::shared_ptr<std::vector<std::shared_ptr<ChannelServer>>> Channels;

struct WorldData
{
  int channelCount = 1;

  int expRate = 1;
  int mesoRate = 1;
  int dropRate = 1;

  int pqExpRate = 1;
  int pqMesoRate = 1;
  int pqDropRate = 1;

  int questExpRate = 1;
  int questMesoRate = 1;
  int questDropRate = 1;

  int bossExpRate = 1;
  int bossMesoRate = 1;
  int bossDropRate = 1;

  int petExpRate = 1;
};

class Master;

class World : public std::enable_shared_from_this<World>
{
  public:
    World();
    World(std::shared_ptr<WorldData> _data) { this->data = _data; }
    ~World();

    // void start(boost::asio::io_context& _ioContext, size_t _port);
    std::shared_ptr<World> getPtr() { return shared_from_this(); }

    void setMaster(std::shared_ptr<Master> _master) { this->master = _master; }
    std::shared_ptr<WorldData> getWorldData() { return this->data; }
    // Channels getChannels() const { return this->channels; }

  private:
    std::shared_ptr<Master> master;
    std::shared_ptr<WorldData> data;
    // Channels channels;
};

#endif