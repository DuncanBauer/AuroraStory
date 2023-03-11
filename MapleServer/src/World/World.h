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
  size_t channelCount = 1;

  size_t expRate = 1;
  size_t mesoRate = 1;
  size_t dropRate = 1;

  size_t pqExpRate = 1;
  size_t pqMesoRate = 1;
  size_t pqDropRate = 1;

  size_t questExpRate = 1;
  size_t questMesoRate = 1;
  size_t questDropRate = 1;

  size_t bossExpRate = 1;
  size_t bossMesoRate = 1;
  size_t bossDropRate = 1;

  size_t petExpRate = 1;
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