#ifndef ADDDRIVES_HPP
#define ADDDRIVES_HPP

#include <QObject>
#include <QString>

class Drives : public QObject
{
    Q_OBJECT
public:
    explicit Drives(QObject *parent = 0);
    void add();

signals:
    void sendDriveLetter(QString driveLetter);

public slots:
};

#endif // ADDDRIVES_HPP
