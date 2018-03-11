#include "usbdrives.hpp"
#include<QString>
#include<QFileInfo>
#include<QDir>
#include<Windows.h>

USBDrives::USBDrives(QObject *parent) : QObject(parent)
{

}

void USBDrives::add()
{
    QDir driveList;
    for(QFileInfo drive : driveList.drives())
    {
        QString driveLetter = drive.absoluteFilePath();
        LPCWSTR driveType = (const wchar_t*) driveLetter.utf16();
        if(GetDriveType(driveType) == 2)
        {
            emit sendUSBDriveLetter(driveLetter);
        }
    }
}
