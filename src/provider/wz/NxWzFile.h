#pragma once

#include <filesystem>

#include "MapleDataProvider.h"

namespace Provider
{
    class NxWzFile : public MapleDataProvider
    {
    public:
        NxWzFile(std::filesystem::path file);

    private:
    };
}