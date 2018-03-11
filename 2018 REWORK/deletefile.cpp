// SWAMI KARUPPASWAMI THUNNAI
#include "deletefile.hpp"

DeleteFile::DeleteFile()
{

}

DeleteFile::DeleteFile(QString fileLocation)
{
    QFile file(fileLocation);
    file.remove();
}
