#include "hash.hpp"

Hash::Hash(QObject *parent) : QObject(parent)
{

}

QString Hash::getMD5(QString i_strFilename)
{
    QByteArray baData=fileChecksum(i_strFilename,QCryptographicHash::Md5);

    if(baData.isEmpty() || baData.isNull())
    {
        return QString();
    }

    return QString(baData.toHex());

}

QString Hash::getSha256(QString i_strFilename)
{
    QByteArray baData=fileChecksum(i_strFilename,QCryptographicHash::Sha256);

    if(baData.isEmpty() || baData.isNull())
    {
        return QString();
    }

    return QString(baData.toHex());
}

QString Hash::getSHA512(QString i_strFilename)
{
    QByteArray baData=fileChecksum(i_strFilename,QCryptographicHash::Sha3_512);

    if(baData.isEmpty() || baData.isNull())
    {
        return QString();
    }

    return QString(baData.toHex());
}

QByteArray Hash::fileChecksum(const QString &fileName,QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile file(fileName);
    if (file.open(QFile::ReadOnly))
    {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&file)) {
            // closed the file
            file.close();
            return hash.result();
        }
        // closed the file
        file.close();
    }
    return QByteArray();
}
