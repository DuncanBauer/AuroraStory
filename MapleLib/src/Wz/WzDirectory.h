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

			std::vector<WzImage> GetImages() { return m_Images; }
			std::vector<WzDirectory> GetSubDirs() { return m_SubDirs; }
			ByteBuffer GetWzIV() { return m_WzIV; }
			unsigned int GetOffset() { return m_Offset; }
			int GetOffsetSize() { return m_OffsetSize; }
			unsigned int GetHash() { return m_Hash; }
			int GetSize() { return m_Size; }
			int GetChecksum() { return m_Checksum; }

		private:
			std::vector<WzImage> m_Images;
			std::vector<WzDirectory> m_SubDirs;
			ByteBuffer m_WzIV;
			unsigned int m_Offset;
			int m_OffsetSize;
			unsigned int m_Hash;
			int m_Size;
			int m_Checksum;

		private:
			friend WzFile;
	};
}