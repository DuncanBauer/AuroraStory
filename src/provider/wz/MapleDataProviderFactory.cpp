#include <filesystem>

#include "MapleDataProviderFactory.h"
#include "WzFile.h"
#include "NxWzFile.h"
#include "XmlWzFile.h"
#include "util/LoggingTool.h"

namespace Provider
{
    MapleDataProvider MapleDataProviderFactory::getWZ(std::filesystem::path file) 
    {
        if (file.string().ends_with("nx"))
        {
            try
            {
                return NxWzFile(file);
            }
            catch (std::exception e)
            {
                SERVER_ERROR("Loading NX File failed: {}", e.what());
            }
        }
        else if (file.string().ends_with("wz") && !std::filesystem::is_directory(file))
        {
            try 
            {
                //return WzFile(file);
            }
            catch (std::exception e)
            {
                SERVER_ERROR("Loading WZ File failed: {}", e.what());
            }
        }
        else 
        {
            try
            {
                //return XmlWzFile(file);
            }
            catch (std::exception e)
            {
                SERVER_ERROR("Loading XML File failed: {}", e.what());
            }
        }
    }

    MapleDataProvider MapleDataProviderFactory::getDataProvider(const std::string& fileIn) 
    {
        return getWZ(fileIn);
    }

    std::filesystem::path MapleDataProviderFactory::fileInWZPath(std::string filename)
    {
        std::filesystem::path file(m_wzPath + filename);
        if (std::filesystem::exists(file))
        {
            return file;
        }

        return;
    }
}