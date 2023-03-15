#pragma once

#include <string>

namespace Wz
{
	class AURORA_MAPLE_API WzHeader
	{
		public:
			WzHeader() = default;
			WzHeader(const WzHeader& other)
			{
				m_Ident = other.m_Ident;
				m_Copyright = other.m_Copyright;
				m_FileStart = other.m_FileStart;
				m_FileSize = other.m_FileSize;
			}

			void RecalculateFileStart()
			{
				m_FileStart = (unsigned int)(m_Ident.length() + sizeof(unsigned long) + sizeof(unsigned int) + m_Copyright.length() + 1);
			}

			static WzHeader GetDefault()
			{
				WzHeader header;
				header.m_Ident = "PKG1";
				header.m_Copyright = "Package file v1.0 Copyright 2002 Wizet, ZMS";
				header.m_FileStart = 60;
				header.m_FileSize = 0;
				return header;
			}

			std::string m_Ident;
			std::string m_Copyright;
			unsigned int m_FileStart = 0;
			unsigned long m_FileSize = 0;
	};

}