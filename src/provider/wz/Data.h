#pragma once

#include <string>
#include <vector>

#include "MapleConstants.h"
#include "DataEntity.h"
#include "nx/nx.h"
#include "nx/node.h"
#include "nx/audio.h"
#include "nx/bitmap.h"
#include "Typedefs.h"

namespace Provider
{
    class Data : public DataEntity
    {
        using MapleDataType = u16;

    public:
        inline MapleDataType getType() { return m_type; }
        inline std::vector<std::shared_ptr<Data>> getChildren() { return m_children; }
        inline std::shared_ptr<Data> getChildByPath(std::string path) 
        { 
            //return m_children[path];
        }
        inline std::shared_ptr<Data> getData() { return m_data; }

    private:
        MapleDataType m_type;
        std::vector<std::shared_ptr<Data>> m_children;
        std::shared_ptr<Data> m_data;
    };
}