#include <iostream>

#include "Maple.h"
#include "Wz/WzFile.h"

#include "Util/BinaryTool.h"

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
		//Util::MemoryMappedFile* mmFile = Util::BinaryTool::MapFile("test.txt");
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadShort(mmFile) << '\n';
		//std::cin.ignore(1000, '\n');




		std::cout << "Writing\n";
		Util::BinaryTool tool("test2.wz", std::ios::binary | std::ios::out);
		tool.WriteByte('a');
		tool.WriteShort((int16_t)1111);
		tool.WriteInt(9999999);
		tool.WriteLong(66666666666);
		tool.WriteFloat(3.2f);
		tool.WriteDouble(3.5);
		tool.WriteString("Wow whata string but what do you know");
		tool.WriteNullTerminatedString("Wow whata string but what do you know");
		tool.close();
		std::cin.ignore(1000, '\n');

		std::cout << "Reading\n";
		tool.open("test2.wz", std::ios::binary | std::ios::in);
		std::cout << tool.ReadByte() << '\n';
		std::cout << tool.ReadShort() << '\n';
		std::cout << tool.ReadInt() << '\n';
		std::cout << tool.ReadLong() << '\n';
		std::cout << tool.ReadFloat() << '\n';
		std::cout << tool.ReadDouble() << '\n';
		std::cout << tool.ReadString(37) << '\n';
		std::cout << tool.ReadNullTerminatedString() << '\n';
		tool.close();
		std::cin.ignore(1000, '\n');




		//Util::MemoryMappedFile* mmFile2 = Util::BinaryTool::MapFile("test2.txt");
		//Util::BinaryTool::WriteByte(mmFile2, 'c');
		//Util::BinaryTool::WriteShort(mmFile2, 2343);
		//Util::BinaryTool::WriteInt(mmFile2, 567576);
		//Util::BinaryTool::WriteLong(mmFile2, 1980109119);
		//std::cin.ignore(1000, '\n');










		//Util::MemoryMappedFile* mmFile = Util::BinaryTool::MapFile("Base.wz");
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cout << Util::BinaryTool::ReadByte(mmFile) << '\n';
		//std::cin.ignore(1000, '\n');

		//character.OpenWzFile("Character.wz");
		//effect.OpenWzFile("Effect.wz");
		//etc.OpenWzFile("Etc.wz");
		//item.OpenWzFile("Item.wz");
		//list.OpenWzFile("List.wz");
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
}