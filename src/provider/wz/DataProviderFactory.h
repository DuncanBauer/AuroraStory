#pragma once

#include "string"

#include "WzDataProvider.h"

namespace Provider
{
    class DataProviderFactory
    {
    public:
        static std::shared_ptr<WzDataProvider> getDataProvider(std::string const& fileIn);
 
    private:
        static std::shared_ptr<WzDataProvider> getWZ(std::filesystem::path file);
        static inline std::string m_wzPath = "wz";
    };
}