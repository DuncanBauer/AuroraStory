#pragma once

#include <filesystem>

#include "DataProvider.h"

namespace Provider
{
    class WzFile : public DataProvider
    {
    public:
        WzFile(std::filesystem::path file);

    private:
    };
}