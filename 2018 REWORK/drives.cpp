// SWAMI KARUPPASWAMI THUNNAI
#include "drives.hpp"
#include<QFileInfo>
#include<QDir>


Drives::Drives(QObject *parent) : QObject(parent)
{

}


void Drives::add()
{
   QDir driveList;
   for(QFileInfo drive : driveList.drives())
   {
        emit sendDriveLetter(drive.absoluteFilePath());
   }
}
