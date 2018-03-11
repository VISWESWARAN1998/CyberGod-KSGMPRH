// SWAMI KARUPPASWAMI THUNNAI
#include "scan.hpp"
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include "scanfile.hpp"

Scan::Scan(QObject *parent) : QObject(parent)
{

}

void Scan::setDrive(QString drive)
{
    this->drive = drive;
}

void Scan::setScanType(QString scanType)
{
    this->scanType = scanType;
}

void Scan::incrementTotalFiles()
{
    totalFilesScannedMutex.lock();
    totalFilesScanned++;
    emit sendScannedFilesCount(totalFilesScanned);
    totalFilesScannedMutex.unlock();
}

void Scan::stopScan()
{
    canScanMutex.lock();
    canScan = false;
    canScanMutex.unlock();
}

void Scan::scanDrive(QString driveLetter)
{
    QStringList supportedFiles;
    if(scanType=="Quick Scan"){
        supportedFiles.append("*.exe");
    } else supportedFiles.append("*.*");
    QDirIterator scanDrive(driveLetter, supportedFiles, QDir::Files, QDirIterator::Subdirectories);
    while(scanDrive.hasNext())
    {
        if(canScan == false) break; // If user has stopped the scan, Then break the loop
        incrementTotalFiles();
        QString currentlyScanningFile = scanDrive.next();
        emit sendCurrentlyScanningFile(currentlyScanningFile);
        qDebug() << currentlyScanningFile;
        ScanFile file(currentlyScanningFile);
        if(file.isMalware())
        {
            ThreatInfo info(file.getThreatName(), currentlyScanningFile);
            emit sendThreatInfo(info);
        }
    }
}

void Scan::scan()
{
    QStringList drivesList;
    if(drive == "all drives")
    {
        QDir dir;
        // append all the drive letter to the drives to be scanned list
        for(QFileInfo driveLetter : dir.drives())
        {
            drivesList.append(driveLetter.absoluteFilePath());
        }
    }
    else drivesList.append(drive);
    foreach(QString driveLetter, drivesList)
    {
        if(canScan == false) break; // If user has stopped the scan, Then break the loop
        qDebug() << "Scanning: " << driveLetter;
        scanDrive(driveLetter);
    }
}
