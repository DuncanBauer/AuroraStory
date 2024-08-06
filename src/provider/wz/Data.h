#pragma once

#include <string>
#include <vector>

#include "MapleConstants.h"
#include "DataEntity.h"
#include "Typedefs.h"

namespace Provider
{
    class Data : public DataEntity
    {
        using MapleDataType = u16;

    public:
        inline MapleDataType                      getType()     { return m_type; }
        inline std::vector<std::shared_ptr<Data>> getChildren() { return m_children; }
        inline std::shared_ptr<Data>              getData()     { return m_data; }
        inline std::shared_ptr<Data>              getChildByPath(std::string path);

    private:
        MapleDataType                      m_type;
        std::vector<std::shared_ptr<Data>> m_children;
        union 
        {
            u32         m_int;
            double      m_double;
            std::string m_string;
            bitmap      m_bitmap;
            vector      m_vector;
            audio       m_audio;
        }
    };
}