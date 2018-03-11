// SWAMI KARUPPASWAMI THUNNAI
#include "executecommand.hpp"

ExecuteCommand::ExecuteCommand(QObject *parent) : QObject(parent)
{

}

void ExecuteCommand::setCommand(QString command)
{
    this->command = command;
}

void ExecuteCommand::execute()
{
    try{
        QProcess::execute(command);
        emit sendExectionInfo(true);
    }
    catch(...){
        emit sendExectionInfo(false);
    }
}

void ExecuteCommand::execute(QString fileLocation)
{
    try
    {
        QProcess process;
        process.setStandardOutputFile(fileLocation);
        process.start(command);
        process.waitForFinished();
    }
    catch(...)
    {
    }
}
