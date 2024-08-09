#pragma once

#include "interfaces/Data.h"
#include "interfaces/DataDirectoryEntry.h"

namespace Provider
{
    class DataProvider
    {
    public:
        virtual std::shared_ptr<DataEntity> getData(std::string const& path) = 0;
        virtual std::shared_ptr<DataEntity> getRoot()                        = 0;
    };
}