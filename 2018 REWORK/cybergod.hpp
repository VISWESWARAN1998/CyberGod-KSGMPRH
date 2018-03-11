#ifndef CYBERGOD_HPP
#define CYBERGOD_HPP

#include <QMainWindow>
#include <QThread>
#include <QMutex>
#include "scan.hpp"
#include "usbscan.hpp"
#include "threatinfo.hpp"

namespace Ui {
class CyberGod;
}

class CyberGod : public QMainWindow
{
    Q_OBJECT

public:
    explicit CyberGod(QWidget *parent = 0);
    ~CyberGod();
public slots:
    // =================================================================================
    //                           SLOTS FOR THE SCAN TAB
    // =================================================================================
    /**
     * @brief scanTabAddDrive This slot is used to add the drives to the drives list
     * combobox present in the scan tab.
     * @param driveLetter The drive letter to be added to the combo box
     */
    void scanTabAddDrive(QString driveLetter);
    /**
     * @brief scanTabUpdateCurrentlyScanningFile This slot is used to update the currently
     * scanning file.
     * @param location The location of the file which is to be updated.
     */
    void scanTabUpdateCurrentlyScanningFile(QString location);
    /**
     * @brief scanTabUpdateCurrentlyScanningFileCount This slot is used to update the
     * total files scanned.
     * @param fileCount count of files which has been scanned.
     */
    void scanTab_updateTotalFilesScanned(unsigned int fileCount);
    /**
     * @brief scanTab_updateThreatInfo This slot is used to update the threat info
     * @param info
     */
    void scanTab_updateThreatInfo(ThreatInfo info);

    // =================================================================================
    //                           SLOTS FOR THE USB TAB
    // =================================================================================
    /**
     * @brief updatePreseneOfAutoRunFile This slot will inform the presence of autorun file
     * in the usb stick.
     */
    void usbTab_updatePreseneOfAutoRunFile(bool isPresent);
    /**
     * @brief updateFileExecutedByAutorun This slot will inform the user what file will be executed
     * in the autorun file.
     * @param file the file which is executed by autorun.
     */
    void usbTab_updateFileExecutedByAutorun(QString file);
    /**
     * @brief usbTab_updateTotalScannedFiles This slot will update the total files scanned on the usb tab.
     * @param fileCount
     */
    void usbTab_updateTotalScannedFiles(unsigned int fileCount);
    /**
     * @brief usbTab_updateCurrentlyScanningFile This method will update the currently scanning file
     * to the font-end which is present in the usb tab.
     * @param location The location of the file to be updated.
     */
    void usbTab_updateCurrentlyScanningFile(QString location);
    /**
     * @brief usbTab_updateThreatInfo This slot is used to update the TableWidget present
     * in the usb tab with the found threat infections.
     * @param info The threat information which is to be updated
     */
    void usbTab_updateThreatInfo(ThreatInfo info);
    /**
     * @brief usbTab_updateAutorunTraceInfo This slot is used to update the autorun table
     * which is present in the USB TAB.
     * @param info The info which is to be updated.
     */
    void usbTab_updateAutorunTraceInfo(ThreatInfo info);
    /**
     * @brief usbTab_informScanCompletion This slot is to inform that the current scan has been complted.
     */
    void usbTab_informScanCompletion();
private slots:
    /**
     * @brief CyberGod::on_scanTab_ScanButton_clicked
     * This method is used to scan the drive for the specified type quick/full
     */
    void on_scanTab_ScanButton_clicked();

    /**
     * @brief usbTab_addDriveToComboBox This slot will add a usb drive to the combo box
     * which is present in the USB TAB.
     * @param driveLetter The drive letter which is to be added to the combo box
     */
    void usbTab_addDriveToComboBox(QString driveLetter);

    /**
     * @brief on_usbTab_scanButton_clicked
     * This method will actually trigger to scan the specified USB drive.
     */
    void on_usbTab_scanButton_clicked();
    //==========================================================
    //          MENU ITEM DECLARATIONS
    //==========================================================
    void on_actionAbout_us_triggered();

    void on_actionFix_shortcut_virus_triggered();

    void on_actionDetect_Rubber_Ducky_triggered();

    void on_actionCustom_Scan_triggered();

    void on_actionThird_party_notices_triggered();

    void on_scanTab_deleteButton_clicked();

private:
    // Private variables declarations
    Ui::CyberGod *ui;
    // For Scan Tab
    QMutex scanTab_scanButtonMutex;
    bool scanTab_toScan = false;
    QMutex usbTab_scanButtonMutex;
    bool usbTab_toScan = false;
    // A thread is used to scan the drive
    QThread scanTab_scanThread;
    // A thread is used to scan the usb drive
    QThread usbTab_scanThread;
    // Private Method declarations
    /**
     * @brief CyberGod::scanTab_changeScanButtonState
     * This method is used to change the state of SCAN button present in the
     * scan tab from START SCAN to STOP SCAN and vice versa. This method is
     * primarily used to notify the user.
     */
    void scanTab_changeScanButtonState();

    void usbTab_changeScanButtonState();

    // Private class declarations
    Scan scan;
    USBScan usbScan;

signals:
    //======================================================
    //    SIGNALS GENERATED BY USB TAB
    //======================================================
    /**
     * @brief usbTab_stopScan send a signal to stop scanning the usb drive
     */
    void usbTab_stopScan();
};

#endif // CYBERGOD_HPP
