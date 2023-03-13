#pragma once

#include "Maple.h"
#include "WzEnums.h"


#include <string>

namespace Wz
{
	class WzFile;




	class AURORA_MAPLE_API WzObject
	{
		public:
			WzObject() {}
			virtual ~WzObject() = 0;

		private:
			std::string m_Name;
			WzObjectType m_Type = WzObjectType::FILE;
			WzObject* m_Parent = nullptr;
			WzFile* m_File = nullptr;

	};
}
