#pragma once

#include "Maple.h"

#include "Wz/WzKey.h"

#include <fstream>
#include <ios>
#include <string>

namespace Util
{
	class AURORA_MAPLE_API MemoryMappedFile
	{
		friend class BinaryTool;
		
		public:
			MemoryMappedFile() = default;
			~MemoryMappedFile();

			char* m_Base = nullptr;
			char* m_Offset = nullptr;
#ifdef _WIN32
			void* m_FileHandle = nullptr;
			void* m_MappingHandle = nullptr;
#else
			int m_FileHandle = 0;
			size_t m_Size = 0;
#endif
	};

	class AURORA_MAPLE_API BinaryTool : public std::fstream
	{
		friend class MemoryMappedFile;
	
		public:
			BinaryTool(const std::string& filename, std::ios_base::openmode mode)
				: std::fstream(filename, mode) {}

			template<typename T>
			BinaryTool& operator<<(const T& data);
			template<typename T>
			BinaryTool& operator>>(T& data);

			byte ReadByte();
			signed char ReadSByte();
			ByteBuffer ReadBytes(int count);
			uint16_t ReadShort();
			int16_t ReadSShort();
			uint32_t ReadInt();
			int32_t ReadSInt();
			int32_t ReadCompressedInt();
			uint64_t ReadLong();
			int64_t ReadSLong();
			float ReadFloat();
			double ReadDouble();
			std::string ReadString(Wz::WzKey* wzKey);
			std::string ReadString(int length);
			std::string ReadNullTerminatedString();
			std::string ReadUnicodeString(int length);

			void Write(byte data);
			void Write(int16_t data);
			void Write(int32_t data);
			void Write(int64_t data);
			void Write(float data);
			void Write(double data);
			void Write(std::string data);
			void Write(std::string data, int length);
			void WriteNullTerminatedString(std::string data);
			void WriteUnicodeString(std::string data);



			/*
					For memory mapped files
			*/
			static MemoryMappedFile* MapFile(std::string filepath);
			static void UnmapFile(MemoryMappedFile* mmFile);

			static byte ReadByte(MemoryMappedFile* mmFile);
			static int16_t ReadShort(MemoryMappedFile* mmFile);
			static int32_t ReadInt(MemoryMappedFile* mmFile);
			static int64_t ReadLong(MemoryMappedFile* mmFile);
			static float ReadFloat(MemoryMappedFile* mmFile);
			static double ReadDouble(MemoryMappedFile* mmFile);
			static std::string ReadString(MemoryMappedFile* mmFile, int length);
			static std::string ReadNullTerminatedString(MemoryMappedFile* mmFile, int length);
			static std::string ReadUnicodeString(MemoryMappedFile* mmFile, int length);

			static void Write(MemoryMappedFile* mmFile, byte data);
			static void Write(MemoryMappedFile* mmFile, int16_t data);
			static void Write(MemoryMappedFile* mmFile, int32_t data);
			static void Write(MemoryMappedFile* mmFile, int64_t data);
			static void Write(MemoryMappedFile* mmFile, float data);
			static void Write(MemoryMappedFile* mmFile, double data);
			static void Write(MemoryMappedFile* mmFile, std::string data);
			static void WriteNullTerminatedString(MemoryMappedFile* mmFile, std::string data);
			static void WriteUnicodeString(MemoryMappedFile* mmFile, std::string data);
	};
}