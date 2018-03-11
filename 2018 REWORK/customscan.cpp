// SWAMI KARUPPASWAMI THUNNAI
#include "customscan.hpp"
#include "ui_customscan.h"
#include <QMessageBox>

CustomScan::CustomScan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomScan)
{
    ui->setupUi(this);

    //==================================================================
    //           CUSTOM SCAN FILE
    //==================================================================
    connect(&customScanFile, SIGNAL(scanCompleted()), this, SLOT(informScanCompleted()));
    connect(&customScanFileThread, SIGNAL(started()), &customScanFile, SLOT(scan()));
    connect(&customScanFile, SIGNAL(sendThreatInfo(ThreatInfo)), this, SLOT(receiveThreatInfo(ThreatInfo)));

}

CustomScan::~CustomScan()
{
    delete ui;
}

void CustomScan::on_customScan_scanButton_clicked()
{
    // If it is a file tjaefd8n
    if(ui->customScan_comboBox->currentText()=="file")
    {
        QString fileLocation = QFileDialog::getOpenFileName(this, tr("Select the file to be scanned"),
                                                            QDir::currentPath(), "*.*");
        ui->customScan_fileLocationLineEdit->setText(fileLocation);
        updateCurrentlyScanningFile(fileLocation);
        if(fileLocation != "")
        {
            customScanFile.setFileToBeScanned(fileLocation);
            customScanFile.moveToThread(&customScanFileThread);
            customScanFileThread.start(QThread::HighestPriority);
        }
    }
    else
    {
        QString folderLocation = QFileDialog::getExistingDirectory(this, tr("Please select your directory"),
                                                                   QDir::currentPath(), QFileDialog::ShowDirsOnly);
        ui->customScan_fileLocationLineEdit->setText(folderLocation);
    }
}

//=====================================================
//          PUBLIC SLOT DEFINITIONS
//=====================================================

void CustomScan::updateCurrentlyScanningFile(QString fileLocation)
{
    ui->customScan_currentlyScanningLabel->setText("Scanning: "+fileLocation);
}

void CustomScan::informScanCompleted()
{
    QMessageBox::information(this, tr("CyberGod KSGMPRH"), tr("Scan has been completed"), QMessageBox::Ok);
}

void CustomScan::receiveThreatInfo(ThreatInfo info)
{
    ui->customScan_threatTable->insertRow(ui->customScan_threatTable->rowCount());
    ui->customScan_threatTable->setItem(ui->customScan_threatTable->rowCount()-1, 0, new QTableWidgetItem(info.getThreatName()));
    ui->customScan_threatTable->setItem(ui->customScan_threatTable->rowCount()-1, 1, new QTableWidgetItem(info.getThreatLocation()));
}
