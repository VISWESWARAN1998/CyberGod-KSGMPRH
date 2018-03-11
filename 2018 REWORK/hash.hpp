#ifndef HASH_H
#define HASH_H

#include <QObject>
#include <QCryptographicHash>
#include <QFile>

class Hash : public QObject
{
    Q_OBJECT

public:

    explicit Hash(QObject *parent = nullptr);

    QString getMD5(QString i_strFilename);
    QString getSha256(QString i_strFilename);
    QString getSHA512(QString i_strFilename);

private:
    QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm);
signals:

public slots:
};

#endif // HASH_H
