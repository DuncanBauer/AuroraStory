#pragma once

#include "string"

#include "MapleDataProvider.h"

namespace Provider
{
    class MapleDataProviderFactory
    {
    public:
        static MapleDataProvider getWZ(std::filesystem::path file);
        static MapleDataProvider getDataProvider(const std::string& fileIn);
        static std::filesystem::path fileInWZPath(std::string filename);
 
    private:
        static std::string m_wzPath;
    };
}