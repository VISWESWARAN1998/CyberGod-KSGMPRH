#ifndef FILE_HPP
#define FILE_HPP

#include <QObject>

class File : public QObject
{
    Q_OBJECT
public:
    explicit File(QObject *parent = 0);

    /**
     * @brief isFilePresent This method will return true if the file is present
     * else it will return false.
     * @param fileLocation The location of the file
     * @return true if the file is present
     */
    bool isFilePresent(QString fileLocation);

    qint64 getFileSize(QString fileLocation);

signals:

public slots:
};

#endif // FILE_HPP
