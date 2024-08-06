#pragma once

#include <string>

namespace Provider
{
    class DataEntity
    {
    public:
        inline std::string getName() { return m_name; }

    protected:
        std::string m_name;
    };
}