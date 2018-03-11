#ifndef USBSCAN_HPP
#define USBSCAN_HPP

#include <QObject>
#include <QString>
#include <QMutex>
#include "threatinfo.hpp"

class USBScan : public QObject
{
    Q_OBJECT
public:
    explicit USBScan(QObject *parent = 0);

    // ====================== PUBLIC METHODS =================
    /**
     * @brief setDrive This method is used to set the drive letter
     * @param driveLetter The drive letter to be assigned.
     */
    void setDrive(QString driveLetter);
    /**
     * @brief stopScan This method is used to stop the scan
     */\
    void stopScan();

signals:
    /**
     * @brief sendPresenceOfAutorunFile will send the presence of autorun file to the frontend
     * @param isAutorunFilePresent true if autorun.inf is present in the USB drive
     */
    void sendPresenceOfAutorunFile(bool isAutorunFilePresent);
    /**
     * @brief sendFileExecutedByAutorun will send the location of the autorun to the front end
     * @param file
     */
    void sendFileExecutedByAutorun(QString file);
    /**
     * @brief sendTotalFilesScannedCount This signal will inform how many files have been scanned actually
     * @param fileCount
     */
    void sendTotalFilesScannedCount(unsigned int fileCount);
    /**
     * @brief sendCurrentlyScanningFile This will signal the frontend so that the user can see what file
     * is being scanned currently.
     * @param location
     */
    void sendCurrentlyScanningFile(QString location);
    /**
     * @brief sendThreatInfo This signal is used to send the threat information to the front end
     * @param info the information about the threat which is to be send.
     */
    void sendThreatInfo(ThreatInfo info);
    /**
     * @brief sendAutorunInfo This signal is used to notify the autorun file traces present in the
     * system to the table widget of USB TAB.
     * @param info
     */
    void sendAutorunInfo(ThreatInfo info);
    /**
     * @brief scanCompleted This signal is used to notify the user that the can has been completed.
     */
    void scanCompleted();

public slots:
    /**
     * @brief checkAutorunFile This method will check whether the autorun file is present or not.
     * @param drive The drive in which the auto run file is to be checked.
     */
    void checkAutorunFile();
    /**
     * @brief getFileExecutedByAutorun This method will get the file executed by autorun
     */
    void getFileExecutedByAutorun();
    /**
     * @brief scan This method is acutually used to scan the usb
     */
    void scan();
private:
    // This variable is used to check whether we can proceed to scan or
    // not. Generally this variable will become false if the use hit the stop button.
    bool canScan = true;
    QMutex canScanMutex;

    // This variable is used to check if the autorun file is present or not
    bool isAutorunPresent = false;

    // The drive to be scanned.
    QString drive;

    // This will be the location of the file executed by the autorun
    QString fileExecutedByAutorun = "";

    // This will be the md5 hash of file executed by the autorun
    QString hashOfFileExecutedByAutorun;

    // This will hold the size of file executed by the autorun
    qint64 sizeOfFileExecutedByAutorun;

    // Total files scanned
    unsigned long int totalFilesScanned = 0;

// Method declarations
private:
    /**
     * @brief incrementTotalFilesScanned This method will increment the total files scanned and send it to the front end.
     */
    void incrementTotalFilesScanned();
};

#endif // USBSCAN_HPP
