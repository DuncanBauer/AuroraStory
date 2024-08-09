#pragma once

#include "DataEntry.h"

namespace Provider
{
    class DataFileEntry : public DataEntry
    {
    public:
        inline void setOffset(int offset) { m_offset = offset; }
    };
}