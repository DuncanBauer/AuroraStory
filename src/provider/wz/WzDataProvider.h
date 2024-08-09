#pragma once

#include "nx/NxNode.h"

namespace Provider
{
    class WzDataProvider
    {
    public:
        virtual NxNode getData(std::string const& path) = 0;
        virtual NxNode getRoot()                        = 0;
    };
}