#pragma once

#include <filesystem>

#include "provider/wz/DataProvider.h"
#include "provider/wz/nx/NxFile.h"

namespace Provider
{
    class NxWzFile : public DataProvider
    {
    public:
        NxWzFile() = delete;
        NxWzFile(std::filesystem::path file);

        std::shared_ptr<DataEntity>         getData(std::string const& path) override;
        std::shared_ptr<DataEntity>         getRoot();
        std::shared_ptr<DataDirectoryEntry> createDirectory(Provider::NxNode& node);

    private:
        Provider::NxFile m_nxFile;
    };
}