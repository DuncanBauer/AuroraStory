#include <iostream>

#include "Maple.h"
#include "Wz/WzFile.h"
#include "Util/WzTool.h"

#include "Util/BinaryTool.h"

int main(int argc, char** argv)
{
	std::cout << "MapleUnitTesting\n";
	try
	{










/*
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
		Wz::WzFile string("String.wz", 83, Wz::WzMapleVersion::GMS);
		Wz::WzFile tamingmob;
		Wz::WzFile ui;

		Util::BinaryTool tool("String.wz", std::ios::binary | std::ios::in);
		
		// Read header
		Wz::WzHeader* header = new Wz::WzHeader();
		header->m_Ident = tool.ReadString(4);
		header->m_FileSize = tool.ReadLong();
		header->m_FileStart = tool.ReadInt();
		header->m_Copyright = tool.ReadNullTerminatedString();
		string.SetHeader(header);
		std::cout << "IDENT: " << header->m_Ident << '\n';
		std::cout << "FSIZE: " << header->m_FileSize << '\n';
		std::cout << "FSTART: " << header->m_FileStart << '\n';
		std::cout << "COPYRIGHT: " << header->m_Copyright << '\n';

		// This is just to clear any buffer space between the header and the file data
		std::cout << "Cursor Pos: " << tool.tellg() << '\n';
		tool.ReadBytes((int)(header->m_FileStart - tool.tellg()));

		// Get file version
		short fileVersion = tool.ReadShort();
		std::cout << "FILE_VERSION: " << fileVersion << '\n';

		// If the file version couldnt be retrieved for some reason
		// we need to try to find it ourselfs
		if (fileVersion == -1)
		{
			throw;
		}

		// parse directorys
		// 
		//this.versionHash = GetVersionHash(version, fileVersion);
		//reader.Hash = this.versionHash;
		//WzDirectory directory = new WzDirectory(reader, this.name, this.versionHash, this.WzIv, this);
		//directory.ParseDirectory();
		//this.wzDir = directory;

		Wz::WzKey* wzKey = new Wz::WzKey(Wz::WzKey::GenerateGMSWzKey());

		std::cout << "IV: ";
		for (int i = 0; i < wzKey->m_IV.size(); i++)
		{
			std::cout << wzKey->m_IV[i] << ' ';
		}
		std::cout << '\n';

		std::cout << "AES KEY: ";
		for (int i = 0; i < wzKey->m_AESKey.size(); i++)
		{
			std::cout << wzKey->m_AESKey[i] << ' ';
		}
		std::cout << '\n';
		std::cout << "AES KEY SIZE: " << wzKey->m_AESKey.size() << '\n';
		std::cin.ignore(1000, '\n');
		
		int32_t entryCount = tool.ReadCompressedInt();
		std::cout << "ENTRY_COUNT: " << entryCount << '\n';
		std::cin.ignore(1000, '\n');

		for (int i = 0; i < entryCount; i++)
		{
			byte type = tool.ReadByte();
			std::string fname = "";
			int32_t fsize, checksum = 0;
			uint32_t offset = 0;
			uint64_t rememberPos = 0;

			if (type == 1)
			{
				int32_t unknownInt = tool.ReadInt();
				int16_t unknownShort = tool.ReadShort();
				uint32_t offset = Util::WzTool::ReadOffset(&tool, &string);
			
				std::cout << "UNKNOWN_INT: " << unknownInt << '\n';
				std::cout << "UNKNOWN_SHORT: " << unknownShort << '\n';
				std::cout << "OFFSET: " << offset << '\n';
			
				continue;
			}
			else if (type == 2)
			{
				int stringOffset = tool.ReadInt();
				rememberPos = tool.tellg();
				tool.seekg(string.GetHeader()->m_FileStart + stringOffset);
				type = tool.ReadByte();
				fname = tool.ReadString(wzKey);

				std::cout << "FNAME: " << fname << '\n';
				std::cout << "TYPE: " << type << '\n';
			}
			else if (type == 3 || type == 4)
			{
				fname = tool.ReadString(wzKey);
				rememberPos = tool.tellg();

				std::cout << "FNAME: " << fname << '\n';
			}
			else
			{
				tool.seekg(rememberPos);
				fsize = tool.ReadCompressedInt();
				checksum = tool.ReadCompressedInt();
				offset = Util::WzTool::ReadOffset(&tool, &string);

				std::cout << "FSIZE: " << fsize << '\n';
				std::cout << "CHECKSUM: " << checksum << '\n';
				std::cout << "OFFSET: " << offset << '\n';
			}
		}

		tool.close();
		std::cin.ignore(1000, '\n');





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
*/
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}
}