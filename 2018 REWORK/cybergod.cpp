// SWAMI KARUPPASWAMI THUNNAI

#include "cybergod.hpp"
#include "ui_cybergod.h"
#include "drives.hpp"
#include "usbdrives.hpp"
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QDebug>

CyberGod::CyberGod(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CyberGod)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("CyberGod KSGMPRH build 0.0.1");
    qRegisterMetaType<ThreatInfo>("ThreatInfo");
    // ===========================================================
    //              SCAN TAB
    // ===========================================================
    // ADD THE DRIVES TO THE UI OF THE SCAN TAB
    Drives drives;
    connect(&drives, SIGNAL(sendDriveLetter(QString)), this, SLOT(scanTabAddDrive(QString)));
    drives.add();
    // ADD OPTION TO SCAN ALL THE DRIVES
    scanTabAddDrive("all drives");
    // ADD THE SCAN TYPE TO THE SCAN TAB
    ui->scanTab_scanTypeComboBox->addItems({"Quick Scan", "Full Scan"});
    // Set the currently scanning file location to NA
    ui->scanTab_currentlyScanningFileLocation->setText("NA");
    // Set the scanned file count to NA
    ui->scanTab_ScannedFilesCount->setText("NA");
    // For the delete button
    ui->scanTab_scanResultTable->setToolTip(tr("You can able to select multiple items by dragging "
                                               "the <b>CURSOR</b> or by holding the <b>CTRL</b> key"));
    // connect signals and slots respectively
    connect(&scanTab_scanThread, SIGNAL(started()), &scan, SLOT(scan()));
    connect(&scan, SIGNAL(sendScannedFilesCount(uint)), this, SLOT(scanTab_updateTotalFilesScanned(uint)));
    connect(&scan, SIGNAL(sendCurrentlyScanningFile(QString)), this, SLOT(scanTabUpdateCurrentlyScanningFile(QString)));
    connect(&scan, SIGNAL(sendThreatInfo(ThreatInfo)), this, SLOT(scanTab_updateThreatInfo(ThreatInfo)));

    // ===========================================================
    //              USB TAB
    // ===========================================================
    USBDrives usbDrives;
    connect(&usbDrives, SIGNAL(sendUSBDriveLetter(QString)), this, SLOT(usbTab_addDriveToComboBox(QString)));
    usbDrives.add();
    // connect the signals and slots necessary to scan USB
    connect(&usbScan, SIGNAL(sendPresenceOfAutorunFile(bool)), this, SLOT(usbTab_updatePreseneOfAutoRunFile(bool)));
    connect(&usbScan, SIGNAL(sendFileExecutedByAutorun(QString)), this, SLOT(usbTab_updateFileExecutedByAutorun(QString)));
    connect(&usbTab_scanThread, SIGNAL(started()), &usbScan, SLOT(scan()));
    connect(&usbScan, SIGNAL(sendTotalFilesScannedCount(uint)), this, SLOT(usbTab_updateTotalScannedFiles(uint)));
    connect(&usbScan, SIGNAL(sendCurrentlyScanningFile(QString)), this, SLOT(usbTab_updateCurrentlyScanningFile(QString)));
    connect(&usbScan, SIGNAL(sendThreatInfo(ThreatInfo)), this, SLOT(usbTab_updateThreatInfo(ThreatInfo)));
    connect(&usbScan, SIGNAL(sendAutorunInfo(ThreatInfo)), this, SLOT(usbTab_updateAutorunTraceInfo(ThreatInfo)));
    connect(&usbScan, SIGNAL(scanCompleted()), this, SLOT(usbTab_informScanCompletion()));
}

CyberGod::~CyberGod()
{
    delete ui;
}

// ====================================================================
//              PUBLIC SLOT DECLARATIONS
// ====================================================================

void CyberGod::scanTabAddDrive(QString driveLetter)
{
    ui->scanTab_DriveComboBox->addItem(driveLetter);
}

void CyberGod::scanTabUpdateCurrentlyScanningFile(QString location)
{
    ui->scanTab_currentlyScanningFileLocation->setText(location);
}

void CyberGod::scanTab_updateTotalFilesScanned(unsigned int fileCount)
{
    ui->scanTab_ScannedFilesCount->setText(QString::number(fileCount));
}

void CyberGod::scanTab_updateThreatInfo(ThreatInfo info)
{
    // Add a new row
    ui->scanTab_scanResultTable->insertRow(ui->scanTab_scanResultTable->rowCount());
    // Add the name of the threat
    ui->scanTab_scanResultTable->setItem(ui->scanTab_scanResultTable->rowCount()-1, 0, new QTableWidgetItem(info.getThreatName()));
    // Add the location of the threat
    ui->scanTab_scanResultTable->setItem(ui->scanTab_scanResultTable->rowCount()-1, 1, new QTableWidgetItem(info.getThreatLocation()));
}


void CyberGod::usbTab_updatePreseneOfAutoRunFile(bool isPresent)
{
    if(isPresent){
        ui->usbTab_autoRunFileLabel->setStyleSheet("QLabel {color: red;}");
        ui->usbTab_autoRunFileLabel->setText("Present");
    }
    else
    {
        ui->usbTab_autoRunFileLabel->setStyleSheet("QLabel {color: green;}");
        ui->usbTab_autoRunFileLabel->setText("Not present");
    }
}

void CyberGod::usbTab_updateFileExecutedByAutorun(QString file)
{
    if(file=="No file executed"){
        ui->usbTab_fileExecutedByAutorunLabel->setStyleSheet("QLabel{color: green;}");
    } else  ui->usbTab_fileExecutedByAutorunLabel->setStyleSheet("QLabel{color: red;}");
    ui->usbTab_fileExecutedByAutorunLabel->setText(file);
}

void CyberGod::usbTab_updateTotalScannedFiles(unsigned int fileCount)
{
    //qDebug() << fileCount;
    ui->usbTab_totalFilesScannedLabel->setText(QString::number(fileCount));
}

void CyberGod::usbTab_updateCurrentlyScanningFile(QString location)
{
    ui->usbTab_currentlyScannigFileLabel->setText(location);
}

void CyberGod::usbTab_updateThreatInfo(ThreatInfo info)
{
    // Add a row
    ui->usbTab_scanResultTable->insertRow(ui->usbTab_scanResultTable->rowCount());
    // Add the name of the threat
    ui->usbTab_scanResultTable->setItem(ui->usbTab_scanResultTable->rowCount()-1, 0, new QTableWidgetItem(info.getThreatName()));
    // Add the location of the threat
    ui->usbTab_scanResultTable->setItem(ui->usbTab_scanResultTable->rowCount()-1, 1, new QTableWidgetItem(info.getThreatLocation()));
}

void CyberGod::usbTab_updateAutorunTraceInfo(ThreatInfo info)
{
    // Add a row
    ui->usbTab_autorunTraceTable->insertRow(ui->usbTab_autorunTraceTable->rowCount());
    // Add the name of the threat
    ui->usbTab_autorunTraceTable->setItem(ui->usbTab_autorunTraceTable->rowCount()-1, 0, new QTableWidgetItem(info.getThreatName()));
    // Add the location of the threat
    ui->usbTab_autorunTraceTable->setItem(ui->usbTab_autorunTraceTable->rowCount()-1, 1, new QTableWidgetItem(info.getThreatLocation()));
}

void CyberGod::usbTab_informScanCompletion()
{
    QMessageBox::information(this, "USB Scan", "Scan completed successfully");
    usbTab_changeScanButtonState();
}

// ====================================================================
//              PRIVATE SLOT DECLARATIONS
// ====================================================================

void CyberGod::on_scanTab_ScanButton_clicked()
{
    scanTab_changeScanButtonState();
    if(scanTab_toScan)
    {
        QString driveLetter = ui->scanTab_DriveComboBox->currentText();
        QString scanType = ui->scanTab_scanTypeComboBox->currentText();
        scan.setDrive(driveLetter);
        scan.setScanType(scanType);
        scan.moveToThread(&scanTab_scanThread);
        scanTab_scanThread.start();
    }
    else{
        scan.stopScan();
        ui->statusBar->showMessage("Stopped the current scan");
    }
}

void CyberGod::on_scanTab_deleteButton_clicked()
{
    QMessageBox::question(this, tr("Confirmation"), tr("Are you sure to delete these items?"), QMessageBox::Yes|QMessageBox::No);
    QList<QTableWidgetItem*> threatLocation = ui->scanTab_scanResultTable->selectedItems();
    foreach(QTableWidgetItem *item, threatLocation)
    {
       QString fileToBeDeleted =  ui->scanTab_scanResultTable->item(item->row(), 1)->text();
       qDebug() << fileToBeDeleted;
    }
}


void CyberGod::on_usbTab_scanButton_clicked()
{
    usbTab_changeScanButtonState();
    if(usbTab_toScan)
    {
        usbScan.checkAutorunFile();
        usbScan.getFileExecutedByAutorun();
        usbScan.moveToThread(&usbTab_scanThread);
        usbTab_scanThread.start();
    }
    else{
        usbScan.stopScan();
    }
}



void CyberGod::usbTab_addDriveToComboBox(QString driveLetter)
{
    ui->usbTab_usbDriveComboBox->addItem(driveLetter);
}

// ====================================================================
//              PRIVATE METHOD DECLARATIONS
// ====================================================================

void CyberGod::scanTab_changeScanButtonState()
{
    scanTab_scanButtonMutex.lock();
    try
    {
        if(!scanTab_toScan)
        {
            ui->scanTab_ScanButton->setText("STOP SCAN");
            scanTab_toScan = true;
        }
        else{
            scanTab_toScan = false;
            ui->scanTab_ScanButton->setText("START SCAN");
        }
    }
    catch(...)
    {

    }
    scanTab_scanButtonMutex.unlock();
}

void CyberGod::usbTab_changeScanButtonState()
{
    usbTab_scanButtonMutex.lock();
    try
    {
        if(!usbTab_toScan)
        {
            ui->usbTab_scanButton->setText("STOP SCAN");
            usbTab_toScan = true;
            // Set the drive letter to be scanned
            usbScan.setDrive(ui->usbTab_usbDriveComboBox->currentText());
        }
        else{
            ui->usbTab_scanButton->setText("START SCAN");
            usbTab_toScan = false;
        }
    }
    catch(...)
    {

    }
    usbTab_scanButtonMutex.unlock();
}

