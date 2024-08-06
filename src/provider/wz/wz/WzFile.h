#pragma once

#include <filesystem>

#include "provider/wz/DataProvider.h"

namespace Provider
{
    class WzFile : public DataProvider
    {
    public:
        WzFile(std::filesystem::path file);

    private:
    };
}