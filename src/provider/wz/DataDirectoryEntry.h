#pragma once

#include "DataEntry.h"
#include "DataFileEntry.h"

namespace Provider
{
    class DataDirectoryEntry : public DataEntry
    {
    public:
        inline std::vector<DataDirectoryEntry> getSubdirectories() { return m_subdirectories; }
        inline std::vector<DataFileEntry> getFiles() { return m_files; }
        DataEntry getEntry(std::string name);

    protected:
        std::vector<DataDirectoryEntry> m_subdirectories;
        std::vector<DataFileEntry> m_files;
    };
}