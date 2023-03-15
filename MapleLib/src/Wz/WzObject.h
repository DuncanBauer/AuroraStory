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
			WzObject() = default;
			WzObject(std::string name) : m_Name(name) {}
			WzObject(std::string name, WzObjectType type) : m_Name(name), m_Type(type) {}
			WzObject(std::string name, WzObjectType type, WzObject* parent) : m_Name(name), m_Type(type), m_Parent(parent) {}
			WzObject(std::string name, WzObjectType type, WzObject* parent, WzFile* wzFile) : m_Name(name), m_Type(type), m_Parent(parent), m_WzFile(wzFile) {}

			std::string GetName()  const { return m_Name; }
			WzObjectType GetType() const { return m_Type; }
			WzObject* GetParent()  const { return m_Parent; }
			WzFile* GetWzFile()    const { return m_WzFile; }

			void SetName(std::string name) { m_Name = name; }
			void SetType(WzObjectType type) { m_Type = type; }
			void SetParent(WzObject* parent) { m_Parent = parent; }
			void SetWzFile(WzFile* wzFile) { m_WzFile = wzFile; }
			
			virtual void ExportXML() = 0;

		protected:
			std::string m_Name;
			WzObjectType m_Type = WzObjectType::FILE;
			WzObject* m_Parent = nullptr;
			WzFile* m_WzFile = nullptr;
	};
}
