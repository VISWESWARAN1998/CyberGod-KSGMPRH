// SWAMI KARUPPASWAMI THUNNAI
#ifndef CUSTOMSCANFILE_HPP
#define CUSTOMSCANFILE_HPP

#include <QObject>
#include <QString>
#include <QThread>
#include "threatinfo.hpp"

/**
 * @brief The CustomScanFile class This class is used to scan the specific file. NOTE: THIS CLASS IS NOTHING BUT A THREADED
 * VERSION OF ScanFile CLASS.
 */
class CustomScanFile : public QObject
{
    Q_OBJECT
public:
    explicit CustomScanFile(QObject *parent = 0);
    /**
     * @brief setFileToBeScanned This method will set the file which is to be scanned
     * @param fileToBeScanned The file location to be scanned
     */
    void setFileToBeScanned(QString fileToBeScanned);

signals:
    /**
     * @brief scanCompleted This signal will be emitted once the scan has been complted
     */
    void scanCompleted();
    /**
     * @brief sendThreatInfo This slot is used to send the threat information to the front end
     * @param info The information which is to be sent for the front end
     */
    void sendThreatInfo(ThreatInfo info);

public slots:
    /**
     * @brief scan This slot is actually used to scan the file
     */
    void scan();

private:
    // This will be the file to be scanned
    QString fileToBeScanned;
};

#endif // CUSTOMSCANFILE_HPP
