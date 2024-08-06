#pragma once

#include <filesystem>

#include "MapleDataProvider.h"

namespace Provider
{
    class WzFile : public MapleDataProvider
    {
    public:
        WzFile(std::filesystem::path file);

    private:
    };
}