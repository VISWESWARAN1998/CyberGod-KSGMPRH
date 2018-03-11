#include "usbscan.hpp"
#include "file.hpp"
#include "hash.hpp"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QStringList>
#include "scanfile.hpp"


USBScan::USBScan(QObject *parent) : QObject(parent)
{

}

void USBScan::stopScan()
{
   canScanMutex.lock();
   try
   {
        canScan = false;
   }
   catch(...)
   {

   }
   canScanMutex.unlock();
}

void USBScan::setDrive(QString driveLetter)
{
    drive = driveLetter;
}

void USBScan::checkAutorunFile()
{
    File file;
    isAutorunPresent = file.isFilePresent(drive+"autorun.inf");
    emit sendPresenceOfAutorunFile(isAutorunPresent);
}

void USBScan::getFileExecutedByAutorun()
{
    // If the autorun is present, get the size
    if(isAutorunPresent){
        File file;
        qint64 autoRunsize = file.getFileSize(drive+"autorun.inf");
        if(autoRunsize>0)
        {
            QFile autorunFile(drive+"autorun.inf");
            if(autorunFile.open(QIODevice::ReadOnly))
            {
                QTextStream stream(&autorunFile);
                while(!stream.atEnd())
                {
                    QString line = stream.readLine();
                    if(line.at(0) == 'o' && line.at(1) == 'p' && line.at(2) == 'e' && line.at(3) == 'n' && line.at(4) == '=')
                    {
                       line = line.replace("open=", "");
                       for(QChar c : line)
                       {
                           if(c==';')break;
                           else
                           {
                               fileExecutedByAutorun = fileExecutedByAutorun + c;
                           }
                       }
                       // specify the drive letter to get the absolute path
                       fileExecutedByAutorun = drive + fileExecutedByAutorun;
                       if(file.isFilePresent(fileExecutedByAutorun))
                       {
                           Hash md5;
                           hashOfFileExecutedByAutorun = md5.getMD5(fileExecutedByAutorun);
                           sizeOfFileExecutedByAutorun = file.getFileSize(fileExecutedByAutorun);
                           emit sendFileExecutedByAutorun(fileExecutedByAutorun);
                       }
                       break;
                    }
                }
                autorunFile.close();
            }
        }
        else
        {
            emit sendFileExecutedByAutorun("No file executed");
        }
    }
}

void USBScan::incrementTotalFilesScanned()
{
    totalFilesScanned++;
    emit sendTotalFilesScannedCount(totalFilesScanned);
}

// This method will be running under different thread
void USBScan::scan()
{
    QDirIterator scanDrive(drive, QStringList() << "*.*", QDir::Files, QDirIterator::Subdirectories);
    while(scanDrive.hasNext())
    {
        if(!canScan)break; // If the user has clicked the STOP button then break the loop
        QString currentlyScanningFile = scanDrive.next();
        incrementTotalFilesScanned();
        emit sendCurrentlyScanningFile(currentlyScanningFile);
        ScanFile file(currentlyScanningFile);
        if(file.isMalware())
        {
            QString threatName =  file.getThreatName();
            ThreatInfo info(threatName, currentlyScanningFile);
            // Emit the signal to inform the user that the threat has been found!
            emit sendThreatInfo(info);
        }
    }
    // Net scan for the autorun files in the system (other drives)
    QDir drives;
    QStringList driveList; // This will hold the list of drives to be scanned.
    for(QFileInfo driveLetter : drives.drives())
    {
        if(driveLetter.absoluteFilePath() != drive)
        {
            driveList.append(driveLetter.absoluteFilePath());
        }
    }
//    driveList.append("E:/sqlite-tools-win32-x86-3210000");
    // Now scan the whole drive for autorun file
    if(hashOfFileExecutedByAutorun.size()== 32)
    {
        Hash hash; // use hash obj for getting the md5
        File file;
        foreach(QString driveLetter, driveList)
        {
            QDirIterator findAutorun(driveLetter, QStringList() << "*.*", QDir::Files, QDirIterator::Subdirectories);
            while(findAutorun.hasNext())
            {
                if(!canScan)break;
                QString currentlyScanningFile = findAutorun.next();
                incrementTotalFilesScanned();
                emit sendCurrentlyScanningFile(currentlyScanningFile);
                qint64 sizeOfFile = file.getFileSize(currentlyScanningFile);
                if(sizeOfFile == sizeOfFileExecutedByAutorun)
                {
                    // If the size matches then go for md5
                    QString md5 = hash.getMD5(currentlyScanningFile);
                    if(md5==hashOfFileExecutedByAutorun){
                        ScanFile file(currentlyScanningFile);
                        if(file.isMalware())
                        {
                            QString threatName =  file.getThreatName();
                            ThreatInfo info(threatName, currentlyScanningFile);
                            // Emit the signal to inform the user that the threat has been found!
                            emit sendAutorunInfo(info);
                        }
                    }
                }
            }
        }
    }
    // Inform to the user that the scan has been complted.
    emit scanCompleted();
}
