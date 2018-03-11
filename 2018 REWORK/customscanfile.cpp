// SWAMI KARUPPASWAMI THUNNAI
#include "customscanfile.hpp"
#include "scanfile.hpp"

CustomScanFile::CustomScanFile(QObject *parent) : QObject(parent)
{

}

//===============================================================
//                  PUBLIC METHOD DEFINITIONS
//===============================================================
void CustomScanFile::setFileToBeScanned(QString fileToBeScanned)
{
    this->fileToBeScanned = fileToBeScanned;
}

//===============================================================
//         PUBLIC SLOT DEFINITIONS
//===============================================================
void CustomScanFile::scan()
{
   ScanFile file(fileToBeScanned);
   if(file.isMalware())
   {
       ThreatInfo info(file.getThreatName(), fileToBeScanned);
       sendThreatInfo(info);
   }
   emit scanCompleted();
}
