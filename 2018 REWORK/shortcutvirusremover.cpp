#include "shortcutvirusremover.hpp"
#include "ui_shortcutvirusremover.h"
#include "drives.hpp"
#include "executecommand.hpp"
#include <QString>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <QMessageBox>
#include <Windows.h>

ShortCutVirusRemover::ShortCutVirusRemover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShortCutVirusRemover)
{
    ui->setupUi(this);
    Drives drives;
    connect(&drives, SIGNAL(sendDriveLetter(QString)), this, SLOT(addDriveToCombobox(QString)));
    drives.add();
    unhideCommand.moveToThread(&unhideFilesThread);
    connect(&unhideFilesThread, SIGNAL(started()), &unhideCommand, SLOT(execute()));
    connect(&unhideCommand, SIGNAL(sendExectionInfo(bool)), this, SLOT(isCommandExecutedSuccessfully(bool)));
    connect(&deleteShortcutThread, SIGNAL(started()), this, SLOT(deleteShortcuts()));
}

ShortCutVirusRemover::~ShortCutVirusRemover()
{
    delete ui;
}

//============================================================
//                  PUBLIC SLOT DEFINITIONS
//============================================================

void ShortCutVirusRemover::addDriveToCombobox(QString driveLetter)
{
    ui->shortcutDialog_driveComboBox->addItem(driveLetter);
}

void ShortCutVirusRemover::addInfoToScanResult(QString info)
{
    ui->shortcutDialog_ResultList->addItem(info);
}

void ShortCutVirusRemover::isCommandExecutedSuccessfully(bool status)
{
    if(status) addInfoToScanResult("Files are un-hidden successfully");
    else addInfoToScanResult("Failed to unhide the files");
}

//============================================================
//                  PRIVATE SLOT DEFINITIONS
//============================================================


void ShortCutVirusRemover::on_shortcutDialog_cleanButton_clicked()
{
    ui->shortcutDialog_cleanButton->setDisabled(true);
    bool shouldFixInfection = false;
    driveLetter = ui->shortcutDialog_driveComboBox->currentText();
    LPCWSTR driveType = (const wchar_t*) driveLetter.utf16();
    // If it is a removable drive directly go fix the infection else ask before fixing
    if(GetDriveType(driveType)==2){
        shouldFixInfection = true;
    }
    else{
        int result = QMessageBox::question(this, "Not a removable drive",
                                           "The drive you selected is not a removable drive, do you want to proceed?",
                                           QMessageBox::Yes | QMessageBox::No);
        shouldFixInfection = (result==QMessageBox::Yes) ? true : false;
    }
    // If not to fix infection return nothing
    if(!shouldFixInfection) return;
    addInfoToScanResult("Fixing the drive: "+driveLetter);
    QString unhideFilesCommandString =  "attrib -h -r -s /s /d ";
    for(QChar c: driveLetter)
    {
        if(c=="/")break;
        unhideFilesCommandString = unhideFilesCommandString + c;
    }
    unhideFilesCommandString = unhideFilesCommandString +"*.*";
    addInfoToScanResult("Sanitizing the hidden files...");
    unhideCommand.setCommand(unhideFilesCommandString);
    unhideFilesThread.start();
    addInfoToScanResult("Deleting all the shortcuts...");
    deleteShortcutThread.start();
    ui->shortcutDialog_cleanButton->setDisabled(false);
}

void ShortCutVirusRemover::deleteShortcuts()
{
    QDirIterator removeLnk(driveLetter, QStringList()<<"*.lnk");
    while(removeLnk.hasNext()){
        QString shortcutFile = removeLnk.next();
        addInfoToScanResult("Found "+shortcutFile);
        try
        {
            QFile file(shortcutFile);
            file.remove();
            addInfoToScanResult("Removed: "+shortcutFile);
        }catch(...){
            addInfoToScanResult("Cannot remove: "+shortcutFile);
        }
    }
}
