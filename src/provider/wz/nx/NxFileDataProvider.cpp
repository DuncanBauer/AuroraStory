#include "NxFileDataProvider.h"

namespace Provider
{
    NxFileDataProvider::NxFileDataProvider(std::filesystem::path file) : m_nxFile(file)
    {}

    NxNode NxFileDataProvider::getData(std::string const& path)
    {
        return m_nxFile.getRoot().resolve(path);
    }

    NxNode NxFileDataProvider::getRoot()
    {
        return m_nxFile.getRoot();
    }
}