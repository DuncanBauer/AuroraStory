#pragma once

#include "DataEntity.h"
#include "Typedefs.h"

namespace Provider
{
    class DataEntry : public DataEntity
    {
    public:
        inline DataEntity getParent()   { return m_parent; }
        inline u32        getSize()     { return m_size; }
        inline u32        getChecksum() { return m_checksum; }
        inline u32        getOffset()   { return m_offset; }

    protected:
        DataEntity m_parent;
        u32        m_size;
        u32        m_checksum;
        u32        m_offset;
    };
}