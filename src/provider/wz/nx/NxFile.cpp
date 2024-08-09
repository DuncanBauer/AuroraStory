#ifdef _WIN32
    #ifdef __MINGW32__
        #include <windows.h>
    #else
        #include <Windows.h>
        #ifdef max
            #undef max
        #endif
        #ifdef min
            #undef min
        #endif
    #endif // __MINGW32__
#else
    #include <cerrno>
    #include <cstring>
    #include <sys/fcntl.h>
    #include <sys/mman.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif
#include <stdexcept>

#include "NxAudio.h"
#include "NxBitmap.h"
#include "NxFile.h"
#include "NxNode.h"

namespace Provider
{
    NxFile::NxFile(std::filesystem::path file)
    {
        open(file);
    }

    NxFile::~NxFile()
    {
        close();
    }

    void NxFile::open(std::filesystem::path file)
    {
        close();
        std::string name = file.string();
        m_data = new NxFileData();

#ifdef _WIN32
        m_data->m_fileHandle = ::CreateFileA(name.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
                                             OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, nullptr);
        if (m_data->m_fileHandle == INVALID_HANDLE_VALUE)
        {
            throw std::runtime_error("Failed to open file " + name);
        }
        
        m_data->m_map = ::CreateFileMappingA(m_data->m_fileHandle, 0, PAGE_READONLY, 0, 0, nullptr);
        if (!m_data->m_map)
        {
            throw std::runtime_error("Failed to create file m_mapping of file " + name);
        }
        
        m_data->m_base = ::MapViewOfFile(m_data->m_map, FILE_MAP_READ, 0, 0, 0);
        if (!m_data->m_base)
        {
            throw std::runtime_error("Failed to m_map view of file " + name);
        }
#else
        m_data->m_fileHandle = ::open(name.c_str(), O_RDONLY);
        if (m_data->m_fileHandle == -1) 
        {
            throw std::runtime_error("Failed to open file " + name + ", errno: " + std::strerror(errno));
        }

        struct stat finfo;
        if (::fstat(m_data->m_fileHandle, &finfo) == -1) 
        {
            throw std::runtime_error("Failed to obtain file information of file " + name + ", errno: " + std::strerror(errno));
        }

        m_data->size = finfo.st_size;
        m_data->m_base = ::mm_map( nullptr, m_data->size, PROT_READ, MAP_SHARED, m_data->m_fileHandle, 0);
        if (m_data->m_base == MAP_FAILED)
        {
            throw std::runtime_error("Failed to create memory m_mapping of file " + name + ", errno: " + std::strerror(errno));
        }
    
    #ifndef NDEBUG
        std::cout << "=== File " << name << " m_mapped to address " << m_data->m_base << " ===\n";
    #endif

#endif

        m_data->m_header = reinterpret_cast<NxFileHeader const*>(m_data->m_base);
        if (m_data->m_header->m_magic != 0x34474B50) 
        {
            throw std::runtime_error(name + " is not a PKG4 NX file (incorrect magic)");
        }

        m_data->m_nodeTable   = reinterpret_cast<NxNodeData const*>(reinterpret_cast<char const*>(m_data->m_base) + m_data->m_header->m_nodeOffset);
        m_data->m_stringTable = reinterpret_cast<uint64_t   const*>(reinterpret_cast<char const*>(m_data->m_base) + m_data->m_header->m_stringOffset);
        m_data->m_bitmapTable = reinterpret_cast<uint64_t   const*>(reinterpret_cast<char const*>(m_data->m_base) + m_data->m_header->m_bitmapOffset);
        m_data->m_audioTable  = reinterpret_cast<uint64_t   const*>(reinterpret_cast<char const*>(m_data->m_base) + m_data->m_header->m_audioOffset);
    }

    void NxFile::close()
    {
        if (!m_data) 
        {
            return;
        }

#ifdef _WIN32
        ::UnmapViewOfFile(m_data->m_base);
        ::CloseHandle(m_data->m_map);
        ::CloseHandle(m_data->m_fileHandle);
#else
        ::munmap(const_cast<void*>(m_data->base), m_data->m_size);
        ::close(m_data->m_fileHandle);
#endif

        delete m_data;
        m_data = nullptr;
    }
}