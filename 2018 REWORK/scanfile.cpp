#include "scanfile.hpp"
#include "file.hpp"
#include "hash.hpp"
#include "hashdatabase.hpp"


ScanFile::ScanFile(QString location)
{
    fileLocation = location;
}


QString ScanFile::getThreatName()
{
    return threatName;
}

QString ScanFile::getThreatType()
{
    return threatType;
}

bool ScanFile::isMalware()
{
    File file;
    if(!file.isFilePresent(fileLocation)) return false;
    HashDatabase database;
    database.initialize();
    Hash hash;
    QString md5 = hash.getMD5(fileLocation);
    QString sha256 = hash.getSha256(fileLocation);
    // If the md5 or the SHA256 is a hash of malware
    if(database.isHashPresent(md5) || database.isHashPresent(sha256))
    {
        threatName = database.getThreatName();
        threatType = database.getThreatType();
        database.close();
        return true;
    }
    return false;
}
