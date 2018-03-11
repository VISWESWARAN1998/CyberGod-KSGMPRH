// SWAMI KARUPPASWAMI THUNNAI
#include "customscanfolder.hpp"

CustomScanFolder::CustomScanFolder(QObject *parent) : QObject(parent)
{

}

//=====================================================
//             PUBLIC METHOD DEFINITIONS
//=====================================================
void CustomScanFolder::setFolderLocation(QString folderLocation)
{
    this->folderLocation = folderLocation;
}

//=====================================================
//             PUBLIC SLOT DEFINITIONS
//=====================================================
void CustomScanFolder::scan()
{
}
