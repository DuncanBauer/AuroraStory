#include "MapleLibPCH.h"

#include "WzFile.h"
#include "WzHeader.h"
#include "WzDirectory.h"
#include "WzTool.h"

#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/mman.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
#endif

namespace Wz
{
	WzFile::WzFile(short gameVersion, WzMapleVersion mapleVersion)
	{
		if (m_Directory)
		{
			delete m_Directory;
		}
		m_Directory = new WzDirectory();
		
		if (m_Header)
		{
			delete m_Header;
		}
		m_Header = new WzHeader();
		WzHeader header = WzHeader::GetDefault();
		m_Header = &header;

		m_FileVersion = gameVersion;
		m_MapleVersion = mapleVersion;
		
		const byte* iv = WzTool::GetIvByMapleVersion(mapleVersion);
		ByteBuffer temp = { iv[0], iv[1], iv[2], iv[3] };
		m_WzIV = temp;
		m_Directory->m_WzIV = m_WzIV;
	}

	WzFile::WzFile(std::string fileName, WzMapleVersion mapleVersion)
	{

	}

	WzFile::WzFile(std::string fileName, short gameVersion, WzMapleVersion mapleVersion)
	{

	}

	WzFile::WzFile(const WzFile& file)
	{
		m_Version = file.m_Version;
		m_VersionHash = file.m_VersionHash;
		m_FileVersion = file.m_FileVersion;
		m_MapleVersion = file.m_MapleVersion;
		m_FilePath = file.m_FilePath;
		m_WzIV = file.m_WzIV;

		if (!m_Header)
		{
			m_Header = new WzHeader();
		}
		m_Header->m_Copyright = file.m_Header->m_Copyright;
		m_Header->m_Ident = file.m_Header->m_Ident;
		m_Header->m_FileSize = file.m_Header->m_FileSize;
		m_Header->m_FileStart = file.m_Header->m_FileStart;

		if (!m_Directory)
		{
			m_Directory = new WzDirectory();
		}
		m_Directory->m_Images = file.m_Directory->m_Images;
		m_Directory->m_SubDirs = file.m_Directory->m_SubDirs;
		m_Directory->m_WzIV = file.m_Directory->m_WzIV;
		m_Directory->m_Offset = file.m_Directory->m_Offset;
		m_Directory->m_OffsetSize = file.m_Directory->m_OffsetSize;
		m_Directory->m_Hash = file.m_Directory->m_Hash;
		m_Directory->m_Size = file.m_Directory->m_Size;
		m_Directory->m_Checksum = file.m_Directory->m_Checksum;
	}

	WzFile::~WzFile()
	{
		delete m_Header;
		delete m_Directory;
		CloseWzFile();
	}

	WzFile& WzFile::operator=(const WzFile& file)
	{
		m_Version = file.m_Version;
		m_VersionHash = file.m_VersionHash;
		m_FileVersion = file.m_FileVersion;
		m_MapleVersion = file.m_MapleVersion;
		m_FilePath = file.m_FilePath;
		m_WzIV = file.m_WzIV;

		if (!m_Header)
		{
			m_Header = new WzHeader();
		}
		m_Header->m_Copyright = file.m_Header->m_Copyright;
		m_Header->m_Ident = file.m_Header->m_Ident;
		m_Header->m_FileSize = file.m_Header->m_FileSize;
		m_Header->m_FileStart = file.m_Header->m_FileStart;

		if (!m_Header)
		{
			m_Directory = new WzDirectory();
		}
		m_Directory->m_Images = file.m_Directory->m_Images;
		m_Directory->m_SubDirs = file.m_Directory->m_SubDirs;
		m_Directory->m_WzIV = file.m_Directory->m_WzIV;
		m_Directory->m_Offset = file.m_Directory->m_Offset;
		m_Directory->m_OffsetSize = file.m_Directory->m_OffsetSize;
		m_Directory->m_Hash = file.m_Directory->m_Hash;
		m_Directory->m_Size = file.m_Directory->m_Size;
		m_Directory->m_Checksum = file.m_Directory->m_Checksum;
	
		return *this;
	}

	void WzFile::OpenWzFile(std::string filepath)
	{
		std::ifstream file(filepath, std::ios::binary | std::ios::ate);
		std::streamsize size = file.tellg();
		
		#ifdef _WIN32
			m_FileHandle = CreateFileA(filepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (m_FileHandle == INVALID_HANDLE_VALUE)
			{
				std::cout << m_FileHandle << '\n';
				throw std::runtime_error("Failed to open file " + filepath);
			}
		
			m_MappingHandle = CreateFileMapping(m_FileHandle, NULL, PAGE_READONLY, 0, size, NULL);
			if (!m_MappingHandle)
			{
				std::cout << m_MappingHandle << '\n';
				throw std::runtime_error("Failed to create file mapping of file " + filepath);
			}
					
			m_Base = MapViewOfFile(m_MappingHandle, FILE_MAP_READ, 0, 0, size);
			if (!m_Base)
			{
				std::cout << m_Base << '\n';
				throw std::runtime_error("Failed to map view of file " + filepath);
			}
		#else
			m_FileHandle = open(filepath, O_RDONLY);
			if (m_FileHandle == -1)
			{
				throw std::runtime_error("Failed to open file " + filepath);
			}
		
			struct stat finfo;
			if (fstat(m_FileHandle, &finfo) == -1)
			{
				throw std::runtime_error("Failed to obtain file information of file " + filepath);
			}
					
			m_Size = finfo.st_size;
			m_Base = mmap(NULL, m_Size, PROT_READ, MAP_SHARED, m_FileHandle, 0);
			if (reinterpret_cast<intptr_t>(base) == -1)
			{
				throw std::runtime_error("Failed to create memory mapping of file " + filepath);
			}
		#endif

		// Output the mapped data to std::cout
		char* pData = static_cast<char*>(m_Base);
		std::cout.write(pData, static_cast<std::streamsize>(GetFileSize(m_FileHandle, NULL)));
	}

	void WzFile::CloseWzFile()
	{
		#ifdef _WIN32
			UnmapViewOfFile(m_Base);
			CloseHandle(m_MappingHandle);
			CloseHandle(m_FileHandle);
		#else
			munmap(const_cast<char*>(m_Base), m_Size);
			close(m_Base);
		#endif
	}

	void WzFile::ParseWzFile()
	{

	}

	void WzFile::ExportWz()
	{
	}
	
	void WzFile::ExportXML()
	{
	}

	void WzFile::GenerateVershionHash()
	{
		m_VersionHash = 0;
		for (char ch : std::to_string(m_FileVersion))
		{
			m_VersionHash = (m_VersionHash * 32) + (byte)ch + 1;
		}
		unsigned int a = (m_VersionHash >> 24) & 0xFF,
			b = (m_VersionHash >> 16) & 0xFF,
			c = (m_VersionHash >> 8) & 0xFF,
			d = (m_VersionHash & 0xFF);
		m_Version = (byte)~(a ^ b ^ c ^ d);
	}
}