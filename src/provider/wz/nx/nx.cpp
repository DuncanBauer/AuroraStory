//////////////////////////////////////////////////////////////////////////////
// NoLifeNx - Part of the NoLifeStory project                               //
// Copyright © 2013 Peter Atashian                                          //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "nx.h"

#include "file.h"
#include "node.h"

#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

namespace nl
{
    namespace nx
    {
        std::vector<std::unique_ptr<file>> files;
        node base, character, effect, etc, item, map, mob, morph, npc, quest, reactor, skill, sound, string, tamingmob, ui;

        bool exists(std::string name)
        {
            return std::ifstream(name).is_open();
        }

        node addFile(std::string name)
        {
            if (!exists(name))
            {
                return {};
            }

            files.emplace_back(new file(name));
            return *files.back();
        }

        void loadAll()
        {
            if (exists("wz/nx/Base.nx"))
            {
                base        =   addFile("wz/nx/Base.nx");
                character   =   addFile("wz/nx/Character.nx");
                effect      =   addFile("wz/nx/Effect.nx");
                etc         =   addFile("wz/nx/Etc.nx");
                item        =   addFile("wz/nx/Item.nx");
                map         =   addFile("wz/nx/Map.nx");
                mob         =   addFile("wz/nx/Mob.nx");
                morph       =   addFile("wz/nx/Morph.nx");
                npc         =   addFile("wz/nx/Npc.nx");
                quest       =   addFile("wz/nx/Quest.nx");
                reactor     =   addFile("wz/nx/Reactor.nx");
                skill       =   addFile("wz/nx/Skill.nx");
                sound       =   addFile("wz/nx/Sound.nx");
                string      =   addFile("wz/nx/String.nx");
                tamingmob   =   addFile("wz/nx/TamingMob.nx");
                ui          =   addFile("wz/nx/UI.nx");
            }
            else if (exists("wz/nx/Data.nx"))
            {
                base        = addFile("wz/nx/Data.nx");
                character   = base["Character"];
                effect      = base["Effect"];
                etc         = base["Etc"];
                item        = base["Item"];
                map         = base["Map"];
                mob         = base["Mob"];
                morph       = base["Morph"];
                npc         = base["Npc"];
                quest       = base["Quest"];
                reactor     = base["Reactor"];
                skill       = base["Skill"];
                sound       = base["Sound"];
                string      = base["String"];
                tamingmob   = base["TamingMob"];
                ui          = base["UI"];
            }
            else
            {
                throw std::runtime_error("Failed to locate nx files.");
            }
        }
    } // namespace nx
} // namespace nl
