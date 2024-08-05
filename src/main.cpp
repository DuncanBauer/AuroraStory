#include <iostream>
#include <memory>
#include <vector>

#include "Master.h"
#include "provider/wz/nx/nx.h"
#include "provider/wz/nx/node.h"
#include "provider/wz/nx/audio.h"
#include "provider/wz/nx/bitmap.h"

void dumpNodeData(nl::node);
void dumpChildData(const nl::node& node);

int main(int argc, char** argv)
{
    //try
    //{
    //    Master& master = Master::getInstance();
    //    master.run();
    //}
    //catch (std::exception e)
    //{
    //    SERVER_ERROR("{}", e.what());
    //}

    try
    {
        nl::nx::loadAll();
        std::cout << "Base.nx: "        << nl::nx::base.size()      << '\n';
        std::cout << "Character.nx: "   << nl::nx::character.size() << '\n';
        std::cout << "Effect.nx: "      << nl::nx::effect.size()    << '\n';
        std::cout << "Etc.nx: "         << nl::nx::etc.size()       << '\n';
        std::cout << "Item.nx: "        << nl::nx::item.size()      << '\n';
        std::cout << "Map.nx: "         << nl::nx::map.size()       << '\n';
        std::cout << "Mob.nx: "         << nl::nx::mob.size()       << '\n';
        std::cout << "Morph.nx: "       << nl::nx::morph.size()     << '\n';
        std::cout << "Npc.nx: "         << nl::nx::npc.size()       << '\n';
        std::cout << "Quest.nx: "       << nl::nx::quest.size()     << '\n';
        std::cout << "Reactor.nx: "     << nl::nx::reactor.size()   << '\n';
        std::cout << "Skill.nx: "       << nl::nx::skill.size()     << '\n';
        std::cout << "Sound.nx: "       << nl::nx::sound.size()     << '\n';
        std::cout << "String.nx: "      << nl::nx::string.size()    << '\n';
        std::cout << "TamingMob.nx: "   << nl::nx::tamingmob.size() << '\n';
        std::cout << "UI.nx: "          << nl::nx::ui.size()        << '\n';

        //dumpNodeData(nl::nx::base);
        //dumpNodeData(nl::nx::character);
        //dumpNodeData(nl::nx::effect);
        //dumpNodeData(nl::nx::etc);
        //dumpNodeData(nl::nx::item);
        //dumpNodeData(nl::nx::map);
        //dumpNodeData(nl::nx::mob);
        //dumpNodeData(nl::nx::morph);
        //dumpNodeData(nl::nx::npc);
        //dumpNodeData(nl::nx::quest);
        //dumpNodeData(nl::nx::reactor);
        //dumpNodeData(nl::nx::skill);
        //dumpNodeData(nl::nx::sound);
        //dumpNodeData(nl::nx::string);
        //dumpNodeData(nl::nx::tamingmob);
        //dumpNodeData(nl::nx::ui);
    }
    catch (std::exception e)
    {
        SERVER_ERROR("{}", e.what());
    }

    std::cin.get();
}

void dumpNodeData(nl::node node)
{
    auto nodeIt = node.begin();
    while (nodeIt != node.end())
    {
        std::cout << '\t' << nodeIt.name() << '\n';
        dumpChildData(nodeIt);
        nodeIt++;
    }
}

void dumpChildData(const nl::node& node)
{
    auto nodeIt = node.begin();
    while (nodeIt != node.end())
    {
        std::cout << "\t\tName: " << nodeIt.name() << '\n';

        auto childNode = nodeIt;
        switch (nodeIt.data_type())
        {
        case nl::node::type::none:
            dumpChildData(childNode);
            break;

        case nl::node::type::integer:
            std::cout << "\t\t\tInt:" << nodeIt.get_integer() << '\n';
            break;
        
        case nl::node::type::real:
            std::cout << "\t\t\Double:" << nodeIt.get_real() << '\n';
            break;
        
        case nl::node::type::string:
            std::cout << "\t\t\tString:" << nodeIt.get_string() << '\n';
            break;
        
        case nl::node::type::vector:
            std::cout << "\t\t\tVector:" << nodeIt.get_vector().first << ", " << nodeIt.get_vector().second << '\n';
            break;
        
        case nl::node::type::audio:
            std::cout << "\t\t\tAudio:" << nodeIt.get_audio().id() << '\n';
            break;
        
        case nl::node::type::bitmap:
            std::cout << "\t\t\tBitmap:" << nodeIt.get_bitmap().id() << '\n';
            break;
        
        default:
            break;
        }

        nodeIt++;
    }
}