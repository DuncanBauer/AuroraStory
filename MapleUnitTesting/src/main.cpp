#include <iostream>

#include "Maple.h"
#include "Wz/WzFile.h"

int main(int argc, char** argv)
{
	std::cout << "MapleUnitTesting\n";
	
	std::cout << "Testing WzLib\n";
	std::cout << "Importing WzFiles\n";
	Wz::WzFile base;
	Wz::WzFile character;
	Wz::WzFile effect;
	Wz::WzFile etc;
	Wz::WzFile item;
	Wz::WzFile list;
	Wz::WzFile map;
	Wz::WzFile mob;
	Wz::WzFile morph;
	Wz::WzFile npc;
	Wz::WzFile quest;
	Wz::WzFile reactor;
	Wz::WzFile skill;
	Wz::WzFile sound;
	Wz::WzFile string;
	Wz::WzFile tamingmob;
	Wz::WzFile ui;

	try
	{
		std::cout << "\n\n\nBase.wz" << '\n';
		base.OpenWzFile("Base.wz");
		std::cin.ignore(1000, '\n');

		//character.OpenWzFile("Character.wz");
		//effect.OpenWzFile("Effect.wz");
		//etc.OpenWzFile("Etc.wz");
		//item.OpenWzFile("Item.wz");

		std::cout << "\n\n\nList.wz" << '\n';
		list.OpenWzFile("List.wz");
		std::cin.ignore(1000, '\n');

		//map.OpenWzFile("Map.wz");
		//mob.OpenWzFile("Mob.wz");
		//morph.OpenWzFile("Morph.wz");
		//npc.OpenWzFile("Npc.wz");
		//quest.OpenWzFile("Quest.wz");
		//reactor.OpenWzFile("Reactor.wz");
		//skill.OpenWzFile("Skill.wz");
		//sound.OpenWzFile("Sound.wz");
		//string.OpenWzFile("String.wz");
		//tamingmob.OpenWzFile("TamingMob.wz");
		//ui.OpenWzFile("UI.wz");
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}

	std::cin.ignore(1000, '\n');
}