#ifndef SCANFILE_HPP
#define SCANFILE_HPP
#include<QString>
/**
 * @brief The ScanFile class This class is used to scan the file for maliciousness
 */\
class ScanFile
{
private:
    QString fileLocation;
    QString threatName;
    QString threatType;
public:
    ScanFile(QString location);
    /**
     * @brief isMalware
     * @return true if the file is a malware
     */
    bool isMalware();
    /**
     * @brief getThreatName This is a getter which is used to get the threat name
     * @return The name of the threat
     */
    QString getThreatName();
    /**
     * @brief getThreatType This method is used to get the type of the threat
     * @return will return the type of the threat
     */
    QString getThreatType();
};

#endif // SCANFILE_HPP
