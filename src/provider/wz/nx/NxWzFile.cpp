#include "NxWzFile.h"
#include "NxFile.h"
#include "util/LoggingTool.h"

namespace Provider
{
    NxWzFile::NxWzFile(std::filesystem::path file) : m_nxFile(file)
    {}

    std::shared_ptr<DataEntity> NxWzFile::getData(std::string const& path)
    {
        std::shared_ptr<DataEntity> retVal;
        NxNode node = m_nxFile.getRoot().resolve(path);
        
        switch (node.getDataType())
        {
        case NxNodeType::NX_NONE:
            retVal = createDirectory(node);
            break;
        case NxNodeType::NX_INT:
            retVal = std::make_shared<IntData>(node.getInt());
            break;
        case NxNodeType::NX_DOUBLE:
            retVal = std::make_shared<DoubleData>(node.getDouble());
            break;
        case NxNodeType::NX_STRING:
            retVal = std::make_shared<StringData>(node.getString());
            break;
        case NxNodeType::NX_VECTOR:
            retVal = std::make_shared<VectorData>(node.getVector());
            break;
        default:
            break;
        }
        
        return retVal;
    }

    std::shared_ptr<DataEntity> NxWzFile::getRoot()
    {
        return std::make_shared<NxNode>(m_nxFile.getRoot());
    }

    std::shared_ptr<DataDirectoryEntry> NxWzFile::createDirectory(Provider::NxNode& node)
    {
        return std::make_shared<DataDirectoryEntry>();
    }
}