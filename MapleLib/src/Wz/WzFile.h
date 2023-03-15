#pragma once

#include "WzObject.h"
#include "WzHeader.h"

namespace Wz
{
	class WzDirectory;

	class AURORA_MAPLE_API WzFile : public WzObject
	{
		public:
			WzFile() = default;
			WzFile(short gameVersion, WzMapleVersion mapleVersion);
			WzFile(std::string fileName, WzMapleVersion mapleVersion);
			WzFile(std::string fileName, short gameVersion, WzMapleVersion mapleVersion);
			WzFile(const WzFile& file);

			~WzFile();

			WzFile& operator=(const WzFile& file);

			void OpenWzFile(std::string fileName);
			void CloseWzFile();
			void ParseWzFile();
			virtual void ExportXML();
			void ExportWz();

			void GenerateVershionHash();

			short GetVersion() { return m_Version; }
			unsigned int GetVersionHash() { return m_VersionHash; }
			short GetFileVersion() { return m_FileVersion; }
			WzMapleVersion GetMapleVersion() { return m_MapleVersion; }
			std::string GetFilePath() { return m_FilePath; }
			WzHeader* GetHeader() { return m_Header; }
			WzDirectory* GetDirectory() { return m_Directory; }
			ByteBuffer GetWzIV() { return m_WzIV; }

		private:
			short m_Version = 0;
			unsigned int m_VersionHash = 0;
			short m_FileVersion = 0;
			WzMapleVersion m_MapleVersion = WzMapleVersion::GMS;
			std::string m_FilePath;
			ByteBuffer m_WzIV;

			WzHeader* m_Header = nullptr;
			WzDirectory* m_Directory = nullptr;
			void* m_Base = nullptr;

		#ifdef _WIN32
			void * m_FileHandle = nullptr;
			void * m_MappingHandle = nullptr;
		#else
			int m_FileHandle = 0;
			size_t m_Size = 0;
		#endif
	};
}