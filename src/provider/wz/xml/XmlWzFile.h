#pragma once

#include <filesystem>

#include "provider/wz/DataProvider.h"

namespace Provider
{
    class XmlWzFile : public DataProvider
    {
    public:
        XmlWzFile(std::filesystem::path file);

    private:
    };
}