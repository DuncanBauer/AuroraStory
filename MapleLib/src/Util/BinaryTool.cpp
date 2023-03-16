#include "MapleLibPCH.h"

#include "BinaryTool.h"

#include <iostream>
#include <fstream>
#include <sstream>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/mman.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
#endif

namespace Util
{
	MemoryMappedFile::~MemoryMappedFile()
	{
		if (m_Base)
		{
			BinaryTool::UnmapFile(this);
		}
	}

	template<typename T>
	BinaryTool& BinaryTool::operator<<(const T& data)
	{
		static_assert(std::is_pod<T>::value, "Only plain old data types can be written");
		write(reinterpret_cast<const char*>(&data), sizeof(T));
		return *this;
	}

	template<typename T>
	BinaryTool& BinaryTool::operator>>(T& data)
	{
		static_assert(std::is_pod<T>::value, "Only plain old data types can be read");
		read(reinterpret_cast<char*>(&data), sizeof(T));
		return *this;
	}

	MemoryMappedFile* BinaryTool::MapFile(std::string filepath)
	{
		MemoryMappedFile* mmFile = new MemoryMappedFile();

		try
		{
#ifdef _WIN32
			mmFile->m_FileHandle = CreateFileA(filepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (mmFile->m_FileHandle == INVALID_HANDLE_VALUE)
			{
				std::cout << mmFile->m_FileHandle << '\n';
				throw std::runtime_error("Failed to open file " + filepath);
			}

			std::streamsize size = GetFileSize(mmFile->m_FileHandle, NULL);
			mmFile->m_MappingHandle = CreateFileMappingA(mmFile->m_FileHandle, NULL, PAGE_READONLY, 0, size, NULL);
			if (!mmFile->m_MappingHandle)
			{
				std::cout << mmFile->m_MappingHandle << '\n';
				throw std::runtime_error("Failed to create file mapping of file " + filepath);
			}

			mmFile->m_Base = (char*)MapViewOfFile(mmFile->m_MappingHandle, FILE_MAP_READ, 0, 0, size);
			if (!mmFile->m_Base)
			{
				std::cout << mmFile->m_Base << '\n';
				throw std::runtime_error("Failed to map view of file " + filepath);
			}
#else
			mmFile->m_FileHandle = open(filepath, O_RDONLY);
			if (mmFile->m_FileHandle == -1)
			{
				throw std::runtime_error("Failed to open file " + filepath);
			}

			struct stat finfo;
			if (fstat(mmFile->m_FileHandle, &finfo) == -1)
			{
				throw std::runtime_error("Failed to obtain file information of file " + filepath);
			}

			mmFile->m_Size = finfo.st_size;
			mmFile->m_Base = mmap(NULL, mmFile->m_Size, PROT_READ, MAP_SHARED, mmFile->m_FileHandle, 0);
			if (reinterpret_cast<intptr_t>(mmFile->m_Base) == -1)
			{
				throw std::runtime_error("Failed to create memory mapping of file " + filepath);
			}
#endif
			mmFile->m_Offset = mmFile->m_Base;
		}
		catch (std::exception e)
		{
			std::cout << e.what() << '\n';
		}

		return mmFile;
	}

	void BinaryTool::UnmapFile(MemoryMappedFile* mmFile)
	{
		try
		{
#ifdef _WIN32
			UnmapViewOfFile(mmFile->m_Base);
			CloseHandle(mmFile->m_MappingHandle);
			CloseHandle(mmFile->m_FileHandle);
#else
			munmap(const_cast<char*>(mmFile->m_Base), mmFile->m_Size);
			close(mmFile->m_Base);
#endif
		}
		catch (std::exception e)
		{
			std::cout << e.what();
		}
	}

	byte BinaryTool::ReadByte(MemoryMappedFile* mmFile)
	{
		return *(mmFile->m_Offset++);
	}

	int16_t BinaryTool::ReadShort(MemoryMappedFile* mmFile)
	{
		return ReadByte(mmFile) << 8 
			 | ReadByte(mmFile);
	}

	int32_t BinaryTool::ReadInt(MemoryMappedFile* mmFile)
	{
		return ReadByte(mmFile) << 24
			 | ReadByte(mmFile) << 16
			 | ReadByte(mmFile) << 8
			 | ReadByte(mmFile);
	}

	int64_t BinaryTool::ReadLong(MemoryMappedFile* mmFile)
	{
		return ((int64_t) ReadByte(mmFile)) << 56
			 | ((int64_t) ReadByte(mmFile)) << 48
			 | ((int64_t) ReadByte(mmFile)) << 40
			 | ((int64_t) ReadByte(mmFile)) << 32
			 | ((int64_t) ReadByte(mmFile)) << 24
			 | ((int64_t) ReadByte(mmFile)) << 16
			 | ((int64_t) ReadByte(mmFile)) << 8
			 |  (int64_t) ReadByte(mmFile);
	}

	float BinaryTool::ReadFloat(MemoryMappedFile* mmFile)
	{
		return 0.0f;
	}

	double BinaryTool::ReadDouble(MemoryMappedFile* mmFile)
	{
		return 0.0;
	}

	std::string BinaryTool::ReadString(MemoryMappedFile* mmFile, int length)
	{
		return std::string();
	}

	std::string BinaryTool::ReadNullTerminatedString(MemoryMappedFile* mmFile, int length)
	{
		return std::string();
	}

	std::string BinaryTool::ReadUnicodeString(MemoryMappedFile* mmFile, int length)
	{
		return std::string();
	}

	void BinaryTool::WriteByte(MemoryMappedFile* mmFile, byte data)
	{
		if (mmFile)
		{
			if (mmFile->m_Base)
			{
				//byte* pData = static_cast<byte*>(mmFile->m_Base);
				//pData[mmFile->m_Offset + offset] = data;
			}
		}
	}

	void BinaryTool::WriteShort(MemoryMappedFile* mmFile, int16_t data)
	{
		WriteByte(mmFile, data & 0xFF);
		WriteByte(mmFile, (data >> 8) & 0xFF);
	}

	void BinaryTool::WriteInt(MemoryMappedFile* mmFile, int32_t data)
	{
		WriteByte(mmFile, data & 0xFF);
		WriteByte(mmFile, (data >> 8) & 0xFF);
		WriteByte(mmFile, (data >> 16) & 0xFF);
		WriteByte(mmFile, (data >> 24) & 0xFF);
	}

	void BinaryTool::WriteLong(MemoryMappedFile* mmFile, int64_t data)
	{
		WriteByte(mmFile, data & 0xFF);
		WriteByte(mmFile, (data >> 8) & 0xFF);
		WriteByte(mmFile, (data >> 16) & 0xFF);
		WriteByte(mmFile, (data >> 24) & 0xFF);
	}

	void BinaryTool::WriteFloat(MemoryMappedFile* mmFile, float data)
	{
	}

	void BinaryTool::WriteDouble(MemoryMappedFile* mmFile, double data)
	{
	}

	void BinaryTool::WriteString(MemoryMappedFile* mmFile, std::string data)
	{
	}

	void BinaryTool::WriteNullTerminatedString(MemoryMappedFile* mmFile, std::string data)
	{
	}

	void BinaryTool::WriteUnicodeString(MemoryMappedFile* mmFile, std::string data)
	{
	}




	byte BinaryTool::ReadByte()
	{
		char result;
		read(&result, 1);

		return result;
	}

	ByteBuffer BinaryTool::ReadBytes(int count)
	{
		ByteBuffer buff(count);
		char c;
		for (int i = 0; i < count; i++)
		{
			read(&c, 1);
			buff.push_back(c);
		}
		return buff;
	}

	int16_t BinaryTool::ReadShort()
	{
		int16_t r1, r2;
		int16_t result = 0;

		r1 = ReadByte();
		r2 = ReadByte();

		result |= r2 << 8;
		result |= r1;

		return result;
	}

	int32_t BinaryTool::ReadInt()
	{
		int32_t r1, r2, r3, r4;
		int32_t result = 0;

		r1 = ReadByte();
		r2 = ReadByte();
		r3 = ReadByte();
		r4 = ReadByte();

		result |= r4 << 24;
		result |= r3 << 16;
		result |= r2 << 8;
		result |= r1;

		return result;
	}

	int64_t BinaryTool::ReadLong()
	{
		int64_t r1, r2, r3, r4,
			    r5, r6, r7, r8;
		int64_t result = 0;

		r1 = ReadByte();
		r2 = ReadByte();
		r3 = ReadByte();
		r4 = ReadByte();
		r5 = ReadByte();
		r6 = ReadByte();
		r7 = ReadByte();
		r8 = ReadByte();

		result |= r8 << 56;
		result |= r7 << 48;
		result |= r6 << 40;
		result |= r5 << 32;
		result |= r4 << 24;
		result |= r3 << 16;
		result |= r2 << 8;
		result |= r1;

		return result;
	}

	float BinaryTool::ReadFloat()
	{
		float data;
		read(reinterpret_cast<char*>(&data), sizeof(float));
		return data;
	}

	double BinaryTool::ReadDouble()
	{
		double data;
		read(reinterpret_cast<char*>(&data), sizeof(double));
		return data;
	}

	std::string BinaryTool::ReadString()
	{
		std::string data;
		return data;
	}

	std::string BinaryTool::ReadString(int length)
	{
		std::string data;
		for (int i = 0; i < length; i++) data += ReadByte();
		return data;
	}

	std::string BinaryTool::ReadNullTerminatedString()
	{
		std::string data;
		char nul= ' ';
		while (nul != '\0')
		{
			nul = ReadByte();
			data += nul;
		}
		return data;
	}

	void BinaryTool::Write(byte data)
	{
		put(data);
	}

	void BinaryTool::Write(int16_t data)
	{
		Write((byte)(data & 0xFF));
		Write((byte)((data >> 8) & 0xFF));
	}

	void BinaryTool::Write(int32_t data)
	{
		Write((byte)(data & 0xFF));
		Write((byte)((data >> 8) & 0xFF));
		Write((byte)((data >> 16) & 0xFF));
		Write((byte)((data >> 24) & 0xFF));
	}

	void BinaryTool::Write(int64_t data)
	{
		Write((byte)(data & 0xFF));
		Write((byte)((data >> 8)  & 0xFF));
		Write((byte)((data >> 16) & 0xFF));
		Write((byte)((data >> 24) & 0xFF));
		Write((byte)((data >> 32) & 0xFF));
		Write((byte)((data >> 40) & 0xFF));
		Write((byte)((data >> 48) & 0xFF));
		Write((byte)((data >> 56) & 0xFF));
	}

	void BinaryTool::Write(float data)
	{
		write(reinterpret_cast<const char*>(&data), sizeof(float));
	}

	void BinaryTool::Write(double data)
	{
		write(reinterpret_cast<const char*>(&data), sizeof(double));
	}

	void BinaryTool::Write(std::string data)
	{
		for (char c : data)
		{
			Write((byte)c);
		}
	}

	void BinaryTool::Write(std::string data, int length)
	{
		for (char c : data)
		{
			Write((byte)c);
		}
	}

	void BinaryTool::WriteNullTerminatedString(std::string data)
	{
		for (char c : data)
		{
			Write((byte)c);
		}
		Write((byte)'\0');
	}

	std::string BinaryTool::EncryptString(std::string stringToDecrypt)
	{
		std::string outputChars(stringToDecrypt.size(), '\0');
		//for (int i = 0; i < stringToDecrypt.size(); i++)
		//	outputChars[i] = (char)(stringToDecrypt[i] ^ ((char)((WzKey[i * 2 + 1] << 8) + WzKey[i * 2])));
		return outputChars;
	}

	std::string BinaryTool::EncryptNonUnicodeString(std::string stringToDecrypt)
	{
		std::string outputChars(stringToDecrypt.size(), '\0');
		//for (int i = 0; i < stringToDecrypt.size(); i++)
		//	outputChars[i] = (char)(stringToDecrypt[i] ^ WzKey[i]);
		return outputChars;
	}

	std::string BinaryTool::DecryptString(std::string stringToDecrypt)
	{
		std::string outputString = "";
		//for (int i = 0; i < stringToDecrypt.size(); i++)
		//	outputString += (char)(stringToDecrypt[i] ^ ((char)((WzKey[i * 2 + 1] << 8) + WzKey[i * 2])));
		return outputString;
	}

	std::string BinaryTool::DecryptNonUnicodeString(std::string stringToDecrypt)
	{
		std::string outputString = "";
		//for (int i = 0; i < stringToDecrypt.size(); i++)
		//	outputString += (char)(stringToDecrypt[i] ^ WzKey[i]);
		return outputString;
	}
}