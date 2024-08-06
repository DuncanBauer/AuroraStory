#include "NxWzFile.h"
#include "NxFile.h"
#include "util/LoggingTool.h"

namespace Provider
{
    NxWzFile::NxWzFile(std::filesystem::path file)
    {
        NxFile nxFile(file);
        fillDataEntities(file, m_root);
    }

    void NxWzFile::fillMapleDataEntities(std::filesystem::path file, DataDirectoryEntry wzdir) 
    {
        for (File file : file.listFiles()) 
        {
            String fileName = file.getName();
            if (file.isDirectory() && !fileName.endsWith(".img")) 
            {
                DataDirectoryEntry newDir = new DataDirectoryEntry(fileName, 0, 0, wzdir);
                wzdir.addDirectory(newDir);
                fillMapleDataEntitys(file, newDir);
            }
            else if (fileName.endsWith(".xml")) 
            {
                wzdir.addFile(new DataFileEntry(fileName.substring(0, fileName.length() - 4), 0, 0, wzdir));
            }
        }
    }

    //Data NxWzFile::getData(std::string path) override
    //{

    //}
}