#include "MapleLibPCH.h"

#include "NxFile.h"

#include <fstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

namespace Nx
{
	void NxFile::Open(std::string fileName)
	{
		std::ifstream file(fileName, std::ios::binary | std::ios::ate);
		std::streamsize size = file.tellg();

		#ifdef _WIN32
			m_Data->m_FileHandle = CreateFileA(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (m_Data->m_FileHandle == INVALID_HANDLE_VALUE)
			{
				throw std::runtime_error("Failed to open file " + fileName);
			}

			m_Data->m_MappingHandle = CreateFileMapping(m_Data->m_FileHandle, NULL, PAGE_READONLY, 0, size, NULL);
			if (!m_Data->m_MappingHandle)
			{
				throw std::runtime_error("Failed to create file mapping of file " + fileName);
			}
			
			m_Data->m_Base = MapViewOfFile(m_Data->m_MappingHandle, FILE_MAP_READ, 0, 0, size);
			if (!m_Data->m_Base)
			{
				throw std::runtime_error("Failed to map view of file " + fileName);
			}
		#else
			m_Data->m_FileHandle = open(fileName, O_RDONLY);
			if (m_Data->m_FileHandle == -1)
			{
				throw std::runtime_error("Failed to open file " + fileName);
			}

			struct stat finfo;
			if (fstat(m_Data->m_FileHandle, &finfo) == -1)
			{
				throw std::runtime_error("Failed to obtain file information of file " + fileName);
			}
			
			m_Data->m_Size = finfo.st_size;
			m_Data->m_Base = mmap(NULL, m_Data->m_Size, PROT_READ, MAP_SHARED, m_Data->m_FileHandle, 0);
			if (reinterpret_cast<intptr_t>(m_data->base) == -1)
			{
				throw std::runtime_error("Failed to create memory mapping of file " + fileName);
			}
		#endif

		m_Data->m_Header = reinterpret_cast<NxHeader const *>(m_Data->m_Base);
		if (m_Data->m_Header->m_Magic != 0x34474B50)
		{
			throw std::runtime_error(fileName + " is not a PKG4 NX file");
		}
		m_Data->m_NodeTable = reinterpret_cast<NxNodeData const *>(reinterpret_cast<char const *>(m_Data->m_Base) + m_Data->m_Header->m_NodeOffset);
		m_Data->m_StringTable = reinterpret_cast<uint64_t const *>(reinterpret_cast<char const *>(m_Data->m_Base) + m_Data->m_Header->m_StringOffset);
		m_Data->m_BitmapTable = reinterpret_cast<uint64_t const *>(reinterpret_cast<char const *>(m_Data->m_Base) + m_Data->m_Header->m_BitmapOffset);
		m_Data->m_AudioTable  = reinterpret_cast<uint64_t const *>(reinterpret_cast<char const *>(m_Data->m_Base) + m_Data->m_Header->m_AudioOffset);
	}

	void NxFile::Close()
	{
		if(!m_Data) { return; }
		#ifdef _WIN32
			UnmapViewOfFile(m_Data->m_Base);
			CloseHandle(m_Data->m_MappingHandle);
			CloseHandle(m_Data->m_FileHandle);
		#else
			munmap(const_cast<char*>(data), size);
			close(fd);
		#endif
	}
}