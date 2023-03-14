#pragma once

#include "Maple.h"

#include "Wz/WzImage.h"

namespace Wz
{
	class AURORA_MAPLE_API WzImageProperty : public WzObject
	{
		public:
			WzImageProperty() {}
			~WzImageProperty() {}

			virtual void WriteValue() {}
			virtual void ExportXML() {}

			WzImage& GetParentImage() const { return *m_ParentImage; }
			WzPropertyType GetPropertyType() const { return m_PropertyType; }
			WzImageProperties& GetWzProperties() const { return *m_WzProperties; }

			void SetParentImage(WzImage* parentImage) { m_ParentImage = parentImage; }
			void SetPropertyType(WzPropertyType propertyType) { m_PropertyType = propertyType; }
			void SetWzProperties(WzImageProperties* wzProperties) { m_WzProperties = wzProperties; }

		private:
			WzImage* m_ParentImage;
			WzPropertyType m_PropertyType;
			WzImageProperties* m_WzProperties;
	};
}