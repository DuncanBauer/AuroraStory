#pragma once

#include "WzObject.h"
#include "WzDirectory.h"

namespace Wz
{
	class WzHeader;

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
			short m_Version;
			unsigned int m_VersionHash;
			short m_FileVersion;
			WzMapleVersion m_MapleVersion;
			std::string m_FilePath;
			WzHeader* m_Header;
			WzDirectory* m_Directory;
			ByteBuffer m_WzIV;
	};
}