#ifndef SCAN_HPP
#define SCAN_HPP

#include <QObject>
#include <QMutex>
#include "threatinfo.hpp"

class Scan : public QObject
{
    Q_OBJECT
public:
    explicit Scan(QObject *parent = 0);
    /**
     * @brief setDrive This method is used to set the drive which is to be scanned
     * @param drive The drive letter
     */
    void setDrive(QString drive);
    /**
     * @brief setScanType This method is used to set the scan type
     * @param scanType  full or quick
     */
    void setScanType(QString scanType);
    /**
     * @brief incrementTotalFiles This method will increment the total files scanned and will update
     * it to the front end
     */
    void incrementTotalFiles();

    /**
     * @brief scanDrive This method will scan the particular drive
     * @param driveLetter
     */
    void scanDrive(QString driveLetter);
    /**
     * @brief stopScan This method is used to stop the scan
     */
    void stopScan();


signals:
    /**
    * @brief sendScannedFilesCount This signal is used to inform the front end about
    * the total no of files scanned by the product.
    */
   void sendScannedFilesCount(unsigned int);
   /**
    * @brief sendCurrentlyScanningFile This signal is used to inform the front end about the currently scanning
    * file
    * @param file The file which is currently scannig
    */
   void sendCurrentlyScanningFile(QString file);
   /**
    * @brief sendThreatInfo This signal is used to inform the front end about the threat information
    * @param info
    */
   void sendThreatInfo(ThreatInfo info);

public slots:
    /**
     * @brief scan This method is actually used to scan the drive(s).
     * This method will be running in a seperate thread.
     */
    void scan();

private:
    // The drive to be scanned
    QString drive;

    // The type of the scan
    QString scanType;

    // This variable is used to check whether the user has stopped the scan [ will be false if the user has stopped the scan]
    volatile bool canScan = true;
    QMutex canScanMutex;

    // This variable will hold the total files scanned
    unsigned long int totalFilesScanned = 0;

    // A mutex for safe increment of the total files
    QMutex totalFilesScannedMutex;
};

#endif // SCAN_HPP
