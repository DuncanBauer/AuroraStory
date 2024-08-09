#pragma once

#include <filesystem>

#include "provider/wz/WzDataProvider.h"
#include "NxFile.h"

namespace Provider
{
    class NxFileDataProvider : public WzDataProvider
    {
    public:
        NxFileDataProvider()                          = delete;
        NxFileDataProvider(NxFileDataProvider const&) = delete;
        NxFileDataProvider(std::filesystem::path file);

        NxNode getData(std::string const& path) override;
        NxNode getRoot()                        override;

    private:
        NxFile m_nxFile;
    };
}