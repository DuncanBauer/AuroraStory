#pragma once

#include "Data.h"
#include "DataDirectoryEntry.h"

namespace Provider
{
    class DataProvider
    {
    public:
        virtual Data getData(std::string path) = 0;
        inline DataDirectoryEntry getRoot() { return m_root; }

    protected:
        Data m_data;
        DataDirectoryEntry m_root;
    };
}