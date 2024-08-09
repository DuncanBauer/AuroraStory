#pragma once

#include "NxAudio.h"
#include "NxBitmap.h"
#include "Typedefs.h"

namespace Provider
{
    enum class NxNodeType : u16
    {
        NX_NONE   = 0,
        NX_INT    = 1,
        NX_DOUBLE = 2,
        NX_STRING = 3,
        NX_VECTOR = 4,
        NX_BITMAP = 5,
        NX_AUDIO  = 6,
    };

    struct bitmap
    {
        u32 index;
        u16 width;
        u16 height;
    };

    struct audio
    {
        u32 index;
        u32 length;
    };

#pragma pack(push, 1)
    class NxNodeData
    {
    public:
        u32        const m_name;
        u32        const m_children;
        u16        const m_childCount;
        NxNodeType const m_nodeType;
        union
        {
            i64    const m_integer;
            double const m_double;
            u32    const m_string;
            i32    const m_vector[2];
            bitmap const m_bitmap;
            audio  const m_audio;
        };
    };
#pragma pack(pop)

    class NxFileData;
    using vector = std::pair<i32, i32>;
    class NxNode
    {
    public:
        NxNode() = default;
        NxNode(NxNodeData const* nodeData, NxFileData const* fileData);

               NxNode      begin()                         const;
               NxNode      end()                           const;
               NxNode&     operator++();
        inline NxNode      operator++(int inc)                   { return { m_data++, m_fileData }; }
        inline bool        operator==(NxNode const& other) const { return m_data == other.m_data; }
        inline bool        operator!=(NxNode const& other) const { return m_data != other.m_data; }
        inline NxNode      operator[](std::string path)    const { return getChild(path); }
        inline NxNode      operator[](char const* path)    const { return getChild(path); }
        
        inline operator    u8()                            const { return static_cast<u8>(getInt()); }
        inline operator    i8()                            const { return static_cast<i8>(getInt()); }
        inline operator    u16()                           const { return static_cast<u16>(getInt()); }
        inline operator    i16()                           const { return static_cast<i16>(getInt()); }
        inline operator    u32()                           const { return static_cast<u32>(getInt()); }
        inline operator    i32()                           const { return static_cast<i32>(getInt()); }
        inline operator    u64()                           const { return static_cast<u64>(getInt()); }
        inline operator    i64()                           const { return static_cast<i64>(getInt()); }
        inline operator    float()                         const { return static_cast<float>(getDouble()); }
        inline operator    double()                        const { return static_cast<double>(getDouble()); }
        inline operator    long double()                   const { return static_cast<long double>(getDouble()); }
        inline operator    std::string()                   const { return getString(); }
        inline operator    vector()                        const { return getVector(); }
        inline operator    NxBitmap()                      const { return getBitmap(); }
        inline operator    NxAudio()                       const { return getAudio(); }
        
               std::string getName()                       const;
               NxNodeType  getDataType()                   const;
               u32         getSize()                       const { return m_data->m_childCount; }
               u32         getChildren()                   const { return m_data->m_children; }
               NxNode      getChild(std::string path)      const;
               i64         getInt(i64 def = 0)             const;
               double      getDouble(double def = 0)       const;
               std::string getString(std::string def = "") const;
               vector      getVector(vector def = {0,0})   const;
               NxBitmap    getBitmap()                     const;
               NxAudio     getAudio()                      const;
               NxNode      resolve(std::string path)       const noexcept;

    public:
        inline i64         toInt()                         const { return m_data->m_integer; }
        inline double      toDouble()                      const { return m_data->m_double; }
               std::string toString()                      const;
        inline vector      toVector()                      const { return { m_data->m_vector[0], m_data->m_vector[0] }; }
               NxBitmap    toBitmap()                      const;
               NxAudio     toAudio()                       const;

    private:
        NxFileData const* m_fileData;
        NxNodeData const* m_data;
    };
}