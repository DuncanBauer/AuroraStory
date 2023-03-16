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


		Wz::WzFile string("String.wz", 83, Wz::WzMapleVersion::GMS);
		Util::BinaryTool tool("String.wz", std::ios::binary | std::ios::in);
		
		// Read header
		std::string Ident = tool.ReadString(4);
		long FSize = tool.ReadLong();
		int FStart = tool.ReadInt();
		std::string Copyright = tool.ReadNullTerminatedString();
		
		std::cout << "IDENT: " << Ident << '\n';
		std::cout << "FSIZE: " << FSize << '\n';
		std::cout << "FSTART: " << FStart << '\n';
		std::cout << "COPYRIGHT: " << Copyright << '\n';

		// This is just to clear any buffer space between the header and the file data
		std::cout << "Cursor Pos: " << tool.tellg() << '\n';
		tool.ReadBytes((int)(FStart - tool.tellg()));

		// Get file version
		short file_version = tool.ReadShort();
		std::cout << "FILE_VERSION: " << file_version << '\n';

		// If the file version couldnt be retrieved for some reason
		if (file_version == -1)
		{
			throw;
		}
		
		string.GetVersionHash = string.GetVersionHash(string.GetVersion(), string.GetFileVersion());
		reader.Hash = this.versionHash;
		WzDirectory directory = new WzDirectory(reader, this.name, this.versionHash, this.WzIv, this);
		directory.ParseDirectory();
		this.wzDir = directory;

		tool.close();



		//std::cout << "Writing\n";
		//Util::BinaryTool tool("test2.wz", std::ios::binary | std::ios::out);
		//tool.Write((byte)'a');
		//tool.Write((int16_t)1111);
		//tool.Write(9999999);
		//tool.Write(66666666666);
		//tool.Write(3.2f);
		//tool.Write(3.5);
		//tool.Write("Wow whata string but what do you know");
		//tool.WriteNullTerminatedString("Wow whata string but what do you know");
		//tool.close();
		//std::cin.ignore(1000, '\n');

		//std::cout << "Reading\n";
		//tool.open("test2.wz", std::ios::binary | std::ios::in);
		//std::cout << tool.ReadByte() << '\n';
		//std::cout << tool.ReadShort() << '\n';
		//std::cout << tool.ReadInt() << '\n';
		//std::cout << tool.ReadLong() << '\n';
		//std::cout << tool.ReadFloat() << '\n';
		//std::cout << tool.ReadDouble() << '\n';
		//std::cout << tool.ReadString(37) << '\n';
		//std::cout << tool.ReadNullTerminatedString() << '\n';
		//tool.close();
		//std::cin.ignore(1000, '\n');


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