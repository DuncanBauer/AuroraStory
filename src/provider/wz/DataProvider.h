#pragma once

#include "Data.h"
#include "DataDirectoryEntry.h"

namespace Provider
{
    template<typename T>
    class DataProvider
    {
    public:
        virtual Data               getData(std::string path) = 0;
        virtual DataDirectoryEntry getRoot()                 = 0;
    };
}