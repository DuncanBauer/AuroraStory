#pragma once

#include <filesystem>

#include "DataProvider.h"

namespace Provider
{
    class XmlWzFile : public DataProvider
    {
    public:
        XmlWzFile(std::filesystem::path file);

    private:
    };
}