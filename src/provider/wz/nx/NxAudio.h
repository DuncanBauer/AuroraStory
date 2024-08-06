#pragma once

#include "Typedefs.h"

namespace Provider
{
    class NxAudio
    {
    public:
        NxAudio(void const* data, u32 length) : m_data(data), m_length(length) {}

        inline void const* getData()   const { return m_data; }
        inline u32         getLength() const { return m_length; }
        inline size_t      getId()     const { return reinterpret_cast<std::size_t>(m_data);; }

    private:
        void const* m_data = nullptr;
        u32         m_length = 0;
    };
}