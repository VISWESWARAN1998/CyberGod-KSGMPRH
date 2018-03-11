// SWAMI KARUPPASWAMI THUNNAI
#include "hashdatabase.hpp"
#include <QMessageBox>
#include <QDebug>

HashDatabase::HashDatabase(QObject *parent) : QObject(parent)
{

}



void HashDatabase::initialize()
{
    database = QSqlDatabase::addDatabase("QSQLITE", "hashConnection");
    database.setDatabaseName("siva.db");
    if(!database.open())
    {
        qDebug() << "Database not found";
    }
    else
    {

    }
}

QString HashDatabase::getThreatName()
{
    return threatName;
}

QString HashDatabase::getThreatType()
{
    return threatType;
}


bool HashDatabase::isHashPresent(QString hash)
{
    QString hashType;
    if(hash.size() == 32)
    {
        hashType = "MD5";
    }
    else if(hash.size() == 64)
    {
        hashType = "SHA256";
    }
    else if(hash.size() == 128)
    {
        hashType = "SHA512";
    }
    else return false;
    QSqlQuery query(database);
    query.prepare("select * from malware where hash=? and hashType=? limit 1");
    query.bindValue(0, hash);
    query.bindValue(1, hashType);
    if(query.exec())
    {
        bool found = query.next();
        threatName = query.value(2).toString();
        threatType = query.value(7).toString();
        return found;
    }
    return false;
}

void HashDatabase::close()
{
    database.close();
    QSqlDatabase::removeDatabase("hashConnection");
}
