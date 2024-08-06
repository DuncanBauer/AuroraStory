#pragma once

#include <filesystem>

#include "MapleDataProvider.h"

namespace Provider
{
    class XmlWzFile : public MapleDataProvider
    {
    public:
        XmlWzFile(std::filesystem::path file);

    private:
    };
}