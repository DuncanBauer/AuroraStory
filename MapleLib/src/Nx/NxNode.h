#pragma once

#include "Maple.h"
#include "NxFile.h"

namespace Nx
{
	enum class NxDataType : uint16_t 
	{
		NONE = 0,
		INTEGER = 1,
		DOUBLE = 2,
		STRING = 3,
		VECTOR = 4,
		BITMAP = 5,
		AUDIO = 6,
	};

	struct AURORA_MAPLE_API NxAudioData
	{
		uint32_t index;
		uint32_t length;
	};

	struct AURORA_MAPLE_API NxBitmapData
	{
		uint32_t index;
		uint16_t width;
		uint16_t height;
	};

	class AURORA_MAPLE_API NxNodeData
	{
		public:
			uint32_t const name;
			uint32_t const children;
			uint16_t const num;
			NxDataType const type;
			union {
				int64_t const ireal;
				double const dreal;
				uint32_t const string;
				int32_t const vector[2];
				NxBitmapData const bitmap;
				NxAudioData const audio;
			};
	};

	class AURORA_MAPLE_API NxNode
	{
		public:
			NxNode();

		private:
			NxNode(NxNodeData const*, NxFileData const*);

		private:
			uint32_t   m_Name;
			uint32_t   m_FirstChildId;
			uint16_t   m_ChildrenCount;
			uint16_t   m_Type;
			NxNodeData m_Data;
			friend NxFile;
	};
}