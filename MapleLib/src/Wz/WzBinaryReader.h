#pragma once

#include "Maple.h"

#include "WzObject.h"
#include "WzFile.h"

namespace Wz
{
	class AURORA_MAPLE_API WzBinaryReader
	{
	public:
	private:
		WzKey m_Key;
		WzHeader m_Header;
		unsigned int m_Hash;
	};
}