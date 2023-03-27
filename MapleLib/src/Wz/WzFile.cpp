#include "WzFile.h"
#include "WzHeader.h"
#include "WzDirectory.h"
#include "../Util/WzTool.h"

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
		
		const byte* iv = Util::WzTool::GetIvByMapleVersion(mapleVersion);
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