#pragma once

#include <filesystem>

#include "NxNode.h"
#include "Typedefs.h"

namespace Provider
{
    class NxNodeData;
    class NxFileDataProvider;

#pragma pack(push, 1)
    class NxFileHeader
    {
    public:
        u32 const m_magic;
        u32 const m_nodeCount;
        u64 const m_nodeOffset;
        u32 const m_stringCount;
        u64 const m_stringOffset;
        u32 const m_bitmapCount;
        u64 const m_bitmapOffset;
        u32 const m_audioCount;
        u64 const m_audioOffset;
    };
#pragma pack(pop)

    class NxFileData
    {
    public:
        void         const* m_base        = nullptr;
        NxFileHeader const* m_header      = nullptr;
        NxNodeData   const* m_nodeTable   = nullptr;
        u64          const* m_stringTable = nullptr;
        u64          const* m_bitmapTable = nullptr;
        u64          const* m_audioTable  = nullptr;
#ifdef _WIN32
        void              * m_fileHandle  = nullptr;
        void              * m_map         = nullptr;
#else
        int                 m_fileHandle  = 0;
        size_t              m_size        = 0;
#endif
    };

    class NxFile
    {
    public:
        NxFile() = delete;
        NxFile(std::filesystem::path file);
        ~NxFile();

        NxFile(NxFile const&)            = delete;
        NxFile& operator=(NxFile const&) = delete;

        void open(std::filesystem::path file);
        void close();
 
        inline operator    NxNode()         const { return getRoot(); }
        
        inline NxNode      getRoot()        const { return NxNode(m_data->m_nodeTable, m_data);}
        inline u32         getNodeCount()   const { return m_data->m_header->m_nodeCount; }
        inline u32         getStringCount() const { return m_data->m_header->m_stringCount; }
        inline u32         getBitmapCount() const { return m_data->m_header->m_bitmapCount; }
        inline u32         getAudioCount()  const { return m_data->m_header->m_audioCount; }
    
    private:
        NxFileData* m_data = nullptr;
    };
}