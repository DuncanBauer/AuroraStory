#pragma once

#include "MapleData.h"
#include "MapleDataDirectoryEntry.h"

namespace Provider
{
    class MapleDataProvider
    {
    public:
        inline MapleData getData(std::string path) { return m_data; }
        inline MapleDataDirectoryEntry getRoot() { return m_root; }

    protected:
        MapleData m_data;
        MapleDataDirectoryEntry m_root;
    };
}