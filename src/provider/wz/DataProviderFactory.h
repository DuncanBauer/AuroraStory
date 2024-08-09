#pragma once

#include "string"

#include "DataProvider.h"

namespace Provider
{
    class DataProviderFactory
    {
    public:
        static std::shared_ptr<DataProvider> getDataProvider(std::string const& fileIn);
 
    private:
        static std::shared_ptr<DataProvider> getWZ(std::filesystem::path file);
        static inline std::string m_wzPath = "wz";
    };
}