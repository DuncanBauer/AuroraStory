#pragma once

#include "Maple.h"

#include "NxNode.h"

namespace Nx
{
	class AURORA_MAPLE_API NxHeader
	{
		public:

		private:
			uint8_t		 m_Magic[4] = { 0x50, 0x4B, 0x47, 0x34 };
			uint32_t	 m_NodeCount = 0;
			NxNode* 	 m_NodeBlockOffset = nullptr; // Nodes must be contiguous
			uint32_t	 m_StringCount = 0;
			OffsetTable* m_StringOffsetTableOffset = nullptr;
			uint32_t	 m_BitmapCount = 0;
			OffsetTable* m_BitmapOffsetTableOffset = nullptr;
			uint32_t	 m_AudioCount = 0;
			OffsetTable* m_AudioOffsetTableOffset = nullptr;
	};

	class AURORA_MAPLE_API NxFile
	{
		public:
			NxFile() {}
			~NxFile() {}

		private:
	};
}