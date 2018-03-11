// SWAMI KARUPPASWAMI THUNNAI
#include "strings.hpp"
#include <QFile>
#include <QTextStream>

Strings::Strings(QObject *parent) : QObject(parent)
{

}

//===============================================================
//                  PUBLIC METHOD DEFINITIONS
//===============================================================
void Strings::setFileLocation(QString location)
{
    fileLocation = location;
}

QStringList Strings::getStrings()
{
    QStringList stringList;
    try
    {
        QFile file(fileLocation);
        if(!file.open(QFile::ReadOnly | QFile::Text)) return stringList;
        QString fileContent = QTextStream(&file).readAll();
        file.close();
        QString stringInBinaryFile = "";
        for(QChar c : fileContent)
        {
            int charValue = c.unicode();
            // check if char value is in ascii range
            if(charValue > 31 && charValue < 127)
            {
                stringInBinaryFile+=c;
            }
            else
            {
                // If size of the string is greater than 5, then add to the list
                if(stringInBinaryFile.size() > 5)
                {
                    stringList.append(stringInBinaryFile);
                }
                // Re-assign to empty string
                stringInBinaryFile = "";
            }
        }
    }
    catch(...)
    {

    }
    return stringList;
}
