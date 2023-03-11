#pragma once

#include "Maple.h"

#include <string>

namespace Maple
{
  class AURORA_MAPLE_API WzObject
  {
    public:
      WzObject(std::string name);
      ~WzObject() {}

      std::string m_Name;
    private:
    };
}
