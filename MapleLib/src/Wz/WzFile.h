#pragma once

#include "WzObject.h"

namespace Wz
{
	class WzHeader;
	class WzDirectory;

	class AURORA_MAPLE_API WzFile : public WzObject
	{
		public:
			WzFile() = default;
			WzFile(std::string fileName) {}

			void ImportWzFile(std::string fileName);
			virtual void ExportXML();
			void ExportWz();

			unsigned int GetVersionHash() { return m_VersionHash; }
			void GenerateVershionHash() 
			{
				m_VersionHash = 0;
				for(char ch: std::to_string(m_FileVersion))
				{
					m_VersionHash = (m_VersionHash * 32) + (byte)ch + 1;
				}
				unsigned int a = (m_VersionHash >> 24) & 0xFF,
										 b = (m_VersionHash >> 16) & 0xFF,
										 c = (m_VersionHash >> 8) & 0xFF,
										 d = (m_VersionHash & 0xFF);
				m_Version = (byte)~(a ^ b ^ c ^ d);
			}

		private:
			short m_Version = 0;
			unsigned int m_VersionHash = 0;
			short m_FileVersion = 0;
			WzMapleVersion m_MapleVersion = WzMapleVersion::GMS;
			std::string m_FilePath;
			WzHeader* m_Header = nullptr;
			WzDirectory* m_Directory = nullptr;
			ByteBuffer m_WzIV;
	};
}