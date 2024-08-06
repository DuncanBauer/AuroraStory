#pragma once

#include "MapleDataEntry.h"

namespace Provider
{
    class MapleDataFileEntry : public MapleDataEntry
    {
    public:
        inline void setOffset(int offset) { m_offset = offset; }
    };
}