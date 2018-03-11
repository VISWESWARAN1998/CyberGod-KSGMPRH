// SWAMI KARUPPASWAMI THUNNAI
#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <QObject>
#include <QString>
#include <QStringList>

/**
 * @brief The Strings class This class is used to get the strings present in the executable
 */
class Strings : public QObject
{
    Q_OBJECT
public:
    explicit Strings(QObject *parent = 0);
    /**
     * @brief setFileLocation This method is used to set the file location
     * @param location The location of the file
     */
    void setFileLocation(QString location);
    /**
     * @brief getStrings This method is used to get the strings present in the executable.
     * @return will return the strings present in the binary file
     */
    QStringList getStrings();
signals:

public slots:

private:
    // This variable holds the location of the file
    QString fileLocation;
};

#endif // STRINGS_HPP
