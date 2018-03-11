// SWAMI KARUPPASWAMI THUNNAI
#ifndef CUSTOMSCAN_HPP
#define CUSTOMSCAN_HPP

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QThread>
#include "customscanfile.hpp"
#include "threatinfo.hpp"

namespace Ui {
class CustomScan;
}

class CustomScan : public QDialog
{
    Q_OBJECT

public:
    explicit CustomScan(QWidget *parent = 0);
    ~CustomScan();

private slots:
    /**
     * @brief on_customScan_scanButton_clicked This slot will be executed when
     * User clicks the scan button.
     */
    void on_customScan_scanButton_clicked();
public slots:
    /**
     * @brief updateCurrentlyScanningFile This slot is used to update the currently scanning file.
     * @param fileLocation The file location which is to be updated.
     */
    void updateCurrentlyScanningFile(QString fileLocation);
    /**
     * @brief completed This slot is used to inform the user that the
     * scan has been completed
     */
    void informScanCompleted();
    /**
     * @brief receiveThreatInfo This slot is used to receive the Threat Information
     * @param info
     */
    void receiveThreatInfo(ThreatInfo info);

private:
    Ui::CustomScan *ui;

    //==================================================
    //       PRIVATE CLASS DECLARATIONS
    //==================================================
    CustomScanFile customScanFile;
    QThread customScanFileThread;
};

#endif // CUSTOMSCAN_HPP
