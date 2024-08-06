#pragma once

#include "MapleDataEntry.h"
#include "MapleDataFileEntry.h"

namespace Provider
{
    class MapleDataDirectoryEntry : public MapleDataEntry
    {
    public:
        inline std::vector<MapleDataDirectoryEntry> getSubdirectories() { return m_subdirectories; }
        inline std::vector<MapleDataFileEntry> getFiles() { return m_files; }
        MapleDataEntry getEntry(std::string name);

    protected:
        std::vector<MapleDataDirectoryEntry> m_subdirectories;
        std::vector<MapleDataFileEntry> m_files;
    };
}