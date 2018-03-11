#include "file.hpp"
#include <QFileInfo>

File::File(QObject *parent) : QObject(parent)
{

}

bool File::isFilePresent(QString fileLocation)
{
    QFileInfo file(fileLocation);
    // If the file exists and it is a file
    if(file.exists() && file.isFile()) return true;
    return false;
}

qint64 File::getFileSize(QString fileLocation)
{
    QFileInfo file(fileLocation);
    return file.size();
}
