// SWAMI KARUPPASWAMI THUNNAI
#ifndef EXECUTECOMMAND_HPP
#define EXECUTECOMMAND_HPP

#include <QObject>
#include <QString>
#include <QProcess>

/**
 * @brief The ExecuteCommand class This class will execute the command(which is usually to be run using CMD)
 */
class ExecuteCommand : public QObject
{
    Q_OBJECT
public:
    explicit ExecuteCommand(QObject *parent = 0);
    /**
     * @brief setCommand
     * @param command
     */
    void setCommand(QString command);

signals:
    /**
     * @brief sendExectionInfo This signal is used to inform whether the command has been
     * executed successfully or not.
     * @param info
     */\
    void sendExectionInfo(bool info);

public slots:
    /**
     * @brief execute This will execute the command. Since, it could be a long running process
     * it should run in a different thread.
     */
    void execute();
    /**
     * @brief execute same as execute(); but will store the output to local file
     * @param fileLocation The location of the file
     */
    void execute(QString fileLocation);

private:
    // The command to be executed
    QString command;
};

#endif // EXECUTECOMMAND_HPP
