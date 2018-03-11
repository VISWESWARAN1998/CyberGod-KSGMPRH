#ifndef SHORTCUTVIRUSREMOVER_HPP
#define SHORTCUTVIRUSREMOVER_HPP

#include <QDialog>
#include <QThread>
#include "executecommand.hpp"

namespace Ui {
class ShortCutVirusRemover;
}

class ShortCutVirusRemover : public QDialog
{
    Q_OBJECT

public:
    explicit ShortCutVirusRemover(QWidget *parent = 0);
    ~ShortCutVirusRemover();

public slots:
    /**
     * @brief addDrives This slot is used to add the drives to the combo box
     * @param driveLetter The letter which is to be added to the combo box
     */
    void addDriveToCombobox(QString driveLetter);
    /**
     * @brief addInfoToScanResult This will add items to the list widget
     * @param info
     */
    void addInfoToScanResult(QString info);
    /**
     * @brief isCommandExecutedSuccessfully This slot is used to find whether the command
     * has been executed successfully or not.
     * @param status the status of the message
     */
    void isCommandExecutedSuccessfully(bool status);

private slots:
    void on_shortcutDialog_cleanButton_clicked();
    /**
     * @brief deleteShortcuts This method is used to delete the shortcuts
     */
    void deleteShortcuts();

private:
    Ui::ShortCutVirusRemover *ui;

    // The drive letter to be scanned
    QString driveLetter = "";

    // A thread which is used to unhide the files
    QThread unhideFilesThread;

    // Used to execute a command which will change the hidden attributes
    ExecuteCommand unhideCommand;

    // A thread which is used to delete the shortcuts
    QThread deleteShortcutThread;
};

#endif // SHORTCUTVIRUSREMOVER_HPP
