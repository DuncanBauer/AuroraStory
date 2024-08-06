#pragma once

#include "Typedefs.h"

namespace Provider
{
    class NxBitmap
    {
    public:
        NxBitmap(void const* data, u16 width, u16 height) : m_data(data), m_width(width), m_height(height) {}

        inline void   const* getData()             const { return m_data; }
        inline u16           getWidth()            const { return m_width; }
        inline u16           getHeight()           const { return m_height; }
        inline u16           getLength()           const { return 4 * m_width * m_height; }
        inline u16           getCompressedLength() const { return *reinterpret_cast<const std::uint32_t*>(m_data); }
        inline size_t        getId()               const { return reinterpret_cast<std::size_t>(m_data); }

    private:
        void const* m_data = nullptr;
        u16         m_width = 0;
        u16         m_height = 0;
    };
}