#include "MapleLibPCH.h"
#include "WzObject.h"

#include <iostream>

namespace Maple
{
  WzObject::WzObject(std::string name) : m_Name(name)
  {

  }

  void WzObject::print()
  {
    std::cout << m_Name << '\n';
  }
}
