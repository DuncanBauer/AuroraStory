#pragma once

#include <string>

namespace Provider
{
    class DataEntity
    {
    public:
        DataEntity() = default;
        DataEntity(std::string name) : m_name(name) {}

        inline std::string getName() { return m_name; }

    protected:
        std::string m_name;
    };
}