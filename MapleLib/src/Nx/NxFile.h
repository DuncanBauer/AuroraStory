#pragma once

#include "Maple.h"

#include "NxNode.h"

#include <string>

namespace Nx
{
	class AURORA_MAPLE_API NxHeader
	{
		public:
			// uint8_t  m_Magic[4] = { 0x50, 0x4B, 0x47, 0x34 };
			
			uint32_t m_Magic,
					 m_NodeCount,
					 m_StringCount,
					 m_BitmapCount,
					 m_AudioCount = 0;

			uint64_t m_NodeOffset,
					 m_StringOffset,
					 m_BitmapOffset,
					 m_AudioOffset = 0;
	};

	class AURORA_MAPLE_API NxFileData
	{
		public:
			void const		 * m_Base = nullptr;
			NxHeader const	 * m_Header = nullptr;
			NxNodeData const * m_NodeTable = nullptr;
			uint64_t const	 * m_StringTable,
							 * m_BitmapTable,
							 * m_AudioTable  = nullptr;

			#ifdef _WIN32
				void * m_FileHandle = nullptr;
				void * m_MappingHandle = nullptr;
			#else
				int m_FileHandle = 0;
				size_t m_Size = 0;
			#endif
	};

	class AURORA_MAPLE_API NxFile
	{
		public:
			NxFile(std::string fileName) { Open(fileName); };
			NxFile(NxFile&&);
			~NxFile() { Close(); }
			
			NxFile& operator=(NxFile&&);

			void Open(std::string fileName);
			void Close();

			NxNode GetRoot() const { return {m_Data->m_NodeTable, m_Data}; }
			std::string GetString(uint32_t id) const { 
				auto const s = reinterpret_cast<char const *>(m_Data->m_Base) + m_Data->m_StringTable[id]; // Get the address of the string by adding the offset of the string to the address of the base object
				return {s + 2, *reinterpret_cast<uint16_t const *>(s)};
			}

			uint32_t GetNodeCount() const { return m_Data->m_Header->m_NodeCount; }
			uint32_t GetStringCount() const { return m_Data->m_Header->m_StringCount; }
			uint32_t GetBitmapCount() const { return m_Data->m_Header->m_BitmapCount; }
			uint32_t GetAudioCount() const { return m_Data->m_Header->m_AudioCount; }

		private:
			NxFileData* m_Data = nullptr;

	};
}