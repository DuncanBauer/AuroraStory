#pragma once

#include "string"

#include "DataProvider.h"

namespace Provider
{
    class DataProviderFactory
    {
    public:
        static DataProvider getWZ(std::filesystem::path file);
        static DataProvider getDataProvider(const std::string& fileIn);
        static std::filesystem::path fileInWZPath(std::string filename);
 
    private:
        static std::string m_wzPath;
    };
}