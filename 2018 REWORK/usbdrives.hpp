#ifndef USBDRIVES_HPP
#define USBDRIVES_HPP

#include <QObject>

/**
 * @brief The USBDrives class This class is primarily used to send signals to the fromt
 */
class USBDrives : public QObject
{
    Q_OBJECT
public:
    explicit USBDrives(QObject *parent = 0);
    void add();

signals:
    void sendUSBDriveLetter(QString driveLetter);

public slots:
};

#endif // USBDRIVES_HPP
