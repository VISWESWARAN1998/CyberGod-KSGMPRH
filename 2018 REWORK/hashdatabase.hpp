// SWAMI KARUPPASWAMI THUNNAI
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class HashDatabase : public QObject
{
    Q_OBJECT
public:
    explicit HashDatabase(QObject *parent = 0);
    void initialize();
    /**
     * @brief isHashPresent This method will check if the hash is present in the database
     * @param hash The hash which is to be checked
     * @return true if the hash is present in the database
     */
    bool isHashPresent(QString hash);
    /**
     * @brief getThreatName
     * @return The name of the threat
     */
    QString getThreatName();
    /**
     * @brief getThreatType get the type of the threat
     * @return
     */
    QString getThreatType();
    /**
     * @brief close This method is used to close the database
     */
    void close();

signals:

public slots:

private:
    QSqlDatabase database;

    // The name of the threat
    QString threatName = "";

    // The type of the threat
    QString threatType = "";


};

#endif // DATABASE_HPP
