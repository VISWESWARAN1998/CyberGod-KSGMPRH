// SWAMI KARUPPASWAMI THUNNAI
#include "rubberduckydetector.hpp"
#include "ui_rubberduckydetector.h"
#include <QFileInfo>
#include <QDir>
#include <Windows.h>
#include <WinUser.h>
#include <QMessageBox>
#include <QException>

RubberDuckyDetector::RubberDuckyDetector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RubberDuckyDetector)
{
    ui->setupUi(this);
    // Initialize the count of usb drives
    initial_usbDrivesCount = getCountOfUSBDevices();
    initial_inputDevicesCount = getCountOfInputDevices();
    checkForKeyStrokeInjectoThread = QtConcurrent::run(this, &RubberDuckyDetector::checkPresenceOfKeyStrokeInjector);
    connect(this, SIGNAL(driveIsKeyStrokeInjector()), this, SLOT(informKeystrokeInjector()));
    connect(this, SIGNAL(driveIsUSB()), this, SLOT(informUSBDrive()));
 }

RubberDuckyDetector::~RubberDuckyDetector()
{
    running = false;
    checkForKeyStrokeInjectoThread.cancel();
    checkForKeyStrokeInjectoThread.waitForFinished();
    delete ui;
}
//=========================================================
//          PRIVATE METHOD DEFINITIONS
//=========================================================
int RubberDuckyDetector::getCountOfUSBDevices()
{
    int totalRemovableDrives = 0;
    QDir driveList;
    for(QFileInfo drive : driveList.drives())
    {
        QString driveLetter = drive.absoluteFilePath();
        LPCWSTR driveType = (const wchar_t*) driveLetter.utf16();
        if(GetDriveType(driveType) == 2)
        {
            totalRemovableDrives++;
        }
    }
    return totalRemovableDrives;
}

int RubberDuckyDetector::getCountOfInputDevices()
{
    try{
    UINT totalDevices;
    GetRawInputDeviceList(NULL, &totalDevices, sizeof(RAWINPUTDEVICELIST));
    return totalDevices;
    }
    catch(...){return 0;}
}

//=========================================================
//        PUBLIC SLOT DEFINITIONS
//=========================================================

void RubberDuckyDetector::checkPresenceOfKeyStrokeInjector()
{
    while(running)
    {
        try{
            // Once a new device is inserted
            int keystrokeDeviceCount = getCountOfInputDevices();
            // If the input devices count increses then it is a keystroking device
            if(keystrokeDeviceCount>initial_inputDevicesCount)
            {
                emit driveIsKeyStrokeInjector();
                initial_inputDevicesCount = keystrokeDeviceCount;
            }
            // If decreases user has unplugged an input device
            if(keystrokeDeviceCount<initial_inputDevicesCount)
            {
                initial_inputDevicesCount = keystrokeDeviceCount;
            }
            int usbDeviceCount = getCountOfUSBDevices();
            // If the usb devices count increases then it is a USB device
            if(usbDeviceCount>initial_usbDrivesCount)
            {
                emit driveIsUSB();
                initial_usbDrivesCount = usbDeviceCount;
            }
            // If decreases user has unplugged an USB device
            if(usbDeviceCount<initial_usbDrivesCount)
            {
                initial_usbDrivesCount = usbDeviceCount;
            }
        } catch(...){}
    }
}

void RubberDuckyDetector::informKeystrokeInjector()
{
    QMessageBox::critical(this, "CRITICAL", "You have inserted a keystroke injector");
}

void RubberDuckyDetector::informUSBDrive()
{
    QMessageBox::information(this, "INFORMATION", "You have inserted a USB device");
}
