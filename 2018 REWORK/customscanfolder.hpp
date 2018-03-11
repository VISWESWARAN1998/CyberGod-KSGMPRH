// SWAMI KARUPPASWAMI THUNNAI
#ifndef CUSTOMSCANFOLDER_HPP
#define CUSTOMSCANFOLDER_HPP

#include <QObject>

/**
 * @brief The CustomScanFolder class This class is used to custom scan
 * a specific folder
 */
class CustomScanFolder : public QObject
{
    Q_OBJECT
public:
    explicit CustomScanFolder(QObject *parent = 0);
    /**
     * @brief setFolderLocation This method is used to set the folder location to be scanned
     * @param folderLocation The location of the folder to be scanned.
     */
    void setFolderLocation(QString folderLocation);

signals:

public slots:
    /**
     * @brief scan This slot will scan the specific folder
     */
    void scan();

private:
    // The location of the folder to be scanned
    QString folderLocation;
};

#endif // CUSTOMSCANFOLDER_HPP
