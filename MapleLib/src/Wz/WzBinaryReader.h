#pragma once

#include "Maple.h"

#include "WzObject.h"
#include "WzFile.h"
#include "WzHeader.h"
#include "WzKey.h"

#include <fstream>

namespace Wz
{
	class AURORA_MAPLE_API WzBinaryReader
	{
	public:
		WzBinaryReader(std::ifstream input, ByteBuffer WzIv)
		{
			m_Key = WzKey::GenerateWzKey(WzIv);
		}
		~WzBinaryReader() {}

		std::string ReadString(long offset) { return ReadString(offset, false); }
		std::string ReadString(long offset, bool readByte)
		{
			long CurrentOffset = m_FileStream.tellg();
			m_FileStream.seekg(offset);
			if (readByte)
			{
				ReadByte();
			}
			std::string ReturnString = ReadString();
			m_FileStream.seekg(CurrentOffset);
			return ReturnString;
		}
		std::string ReadString(int length);
		std::string ReadString();
		std::string ReadStringBlock();
		std::string ReadNullTerminatedString();
		int ReadCompressedInt();
		long ReadLong();
		unsigned int ReadOffset();

		std::string DecryptString(std::string string);
		std::string DecryptNonUnicodeString(std::string string);
	
	private:
		WzKey m_Key;
		WzHeader m_Header;
		unsigned int m_Hash;
		std::ifstream m_FileStream;
	};
}