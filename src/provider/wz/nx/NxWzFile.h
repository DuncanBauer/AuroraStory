#pragma once

#include <filesystem>

#include "provider/wz/DataProvider.h"

namespace Provider
{
    class NxWzFile : public DataProvider
    {
    public:
        NxWzFile() = delete;
        NxWzFile(std::filesystem::path file);

        void fillDataEntities(std::filesystem::path file, DataDirectoryEntry wzdir);
        //Data getData(std::string path) override;

    private:
    };
}