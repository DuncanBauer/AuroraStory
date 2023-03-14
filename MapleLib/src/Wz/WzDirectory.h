#pragma once

#include "Maple.h"

#include "WzImage.h"

namespace Wz
{
	class AURORA_MAPLE_API WzDirectory : public WzObject
	{
		public:
			WzDirectory() : m_Offset(0), m_OffsetSize(0), m_Hash(0), m_Size(0), m_Checksum(0) {}
			~WzDirectory() {}
			
			virtual void ExportXML() {}

			void ParseDirectory() {}
			void GetDirectory() {}
			void SaveDirectory() {}
			void ClearDirectory() {}
			void AddDirectory() {}
			void DeleteDirectory() {}

			void ParseImages() {}
			void GetImage() {}
			void SaveImages() {}
			void ClearImages() {}
			void AddImage() {}
			void DeleteImage() {}

		private:
			std::vector<WzImage> m_Images;
			std::vector<WzDirectory> m_SubDirs;
			ByteBuffer m_WzIV;
			unsigned int m_Offset;
			int m_OffsetSize;
			unsigned int m_Hash;
			int m_Size;
			int m_Checksum;
	};
}