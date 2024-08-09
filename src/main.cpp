#include <iostream>
#include <memory>
#include <vector>

#include "Master.h"
#include "provider/wz/nx/NxFile.h"

void uhhh(Provider::NxNode node, std::string whitespace);
int main(int argc, char** argv)
{
    try
    {
        //Provider::NxFile file1("wz/nx/Base.nx");
        //std::string str = "";
        //uhhh(file1.getRoot(), str);

        //Provider::NxNode node = file1.getRoot().operator[]("StandardPDD.img/1/100");
        //Provider::NxNode node = file1.getRoot()["StandardPDD.img"];
        //node = node["0"];

        //Provider::NxNode childNode = node["0"];
        //std::cout << childNode.getName() << ": " << (u32)childNode.getDataType() << ": " << childNode.getSize() << '\n'; childNode++;
        //std::cout << childNode.getName() << ": " << (u32)childNode.getDataType() << ": " << childNode.getSize() << '\n'; childNode++;
        //std::cout << childNode.getName() << ": " << (u32)childNode.getDataType() << ": " << childNode.getSize() << '\n'; childNode++;
        //std::cout << childNode.getName() << ": " << (u32)childNode.getDataType() << ": " << childNode.getSize() << '\n'; childNode++;
        //std::cout << childNode.getName() << ": " << (u32)childNode.getDataType() << ": " << childNode.getSize() << '\n'; childNode++;
        //std::cout << childNode.getName() << ": " << (u32)childNode.getDataType() << ": " << childNode.getSize() << '\n';
        
        //std::cout << node.getName() << ": " << (u32)node.getDataType() << ": " << node.getSize() << '\n'; node++;
        //std::cout << node.getName() << ": " << (u32)node.getDataType() << ": " << node.getSize() << '\n'; node++;
        //std::cout << node.getName() << ": " << (u32)node.getDataType() << ": " << node.getSize() << '\n'; node++;
        //std::cout << node.getName() << ": " << (u32)node.getDataType() << ": " << node.getSize() << '\n'; node++;
        //std::cout << node.getName() << ": " << (u32)node.getDataType() << ": " << node.getSize() << '\n'; node++;
        //std::cout << node.getName() << ": " << (u32)node.getDataType() << ": " << node.getSize() << '\n';


        //Provider::NxNode node1 = file1.getRoot().resolve("StandardPDD.img/0");
        //std::cout << "Node1\n";
        //std::cout << node1.getName() << ": " << (u32)node1.getDataType() << ": " 
        //          << node1.getSize() << '\n'; node1++;


        //Provider::NxFile file2("wz/nx/Character.nx");
        //Provider::NxFile file3("wz/nx/Effect.nx");
        //Provider::NxFile file4("wz/nx/Etc.nx");
        //Provider::NxFile file5("wz/nx/Item.nx");
        //Provider::NxFile file6("wz/nx/Map.nx");
        //Provider::NxFile file7("wz/nx/Mob.nx");
        //Provider::NxFile file8("wz/nx/Morph.nx");
        //Provider::NxFile file9("wz/nx/Npc.nx");
        //Provider::NxFile file10("wz/nx/Quest.nx");
        //Provider::NxFile file11("wz/nx/Reactor.nx");
        //Provider::NxFile file12("wz/nx/Skill.nx");
        //Provider::NxFile file13("wz/nx/Sound.nx");
        //Provider::NxFile file14("wz/nx/String.nx");
        //Provider::NxFile file15("wz/nx/TamingMob.nx");
        //Provider::NxFile file16("wz/nx/UI.nx");

        Master& master = Master::getInstance();
        master.run();
    }
    catch (std::exception e)
    {
        SERVER_ERROR("{}", e.what());
    }

    std::cin.get();
}

void uhhh(Provider::NxNode node, std::string whitespace)
{
    auto it = node.begin();
    while (it != node.end())
    {
        std::cout << whitespace << "NAME: " << it.getName() << '\n';
        switch (it.getDataType())
        {
        case Provider::NxNodeType::NX_NONE:
            uhhh(it, whitespace + '\t');
            break;
        case Provider::NxNodeType::NX_INT:
            std::cout << whitespace << "INT: " << it.getInt() << '\n';
            break;
        case Provider::NxNodeType::NX_DOUBLE:
            std::cout << whitespace << "DOUBLE: " << it.getDouble() << '\n';
            break;
        case Provider::NxNodeType::NX_STRING:
            std::cout << whitespace << "STRING: " << it.getString() << '\n';
            break;
        case Provider::NxNodeType::NX_VECTOR:
            std::cout << whitespace << "VECTOR: " << it.getVector().first << ", " << it.getVector().second << '\n';
            break;
        default:
            break;
        }

        it++;
    }
}