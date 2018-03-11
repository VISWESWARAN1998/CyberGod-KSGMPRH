#ifndef THREATINFO_HPP
#define THREATINFO_HPP

#include <QString>

/**
 * @brief The ThreatInfo class This class will be used to send the threat info
 * to the front end
 */
class ThreatInfo
{
private:
    QString threatName;
    QString threatLocation;
public:
    ThreatInfo();
    /**
     * @brief ThreatInfo The constructor is used to set the private variables.
     * @param threatName The name of the threat
     * @param threatLocation The location of the threat
     */
    ThreatInfo(QString threatName, QString threatLocation);
    /**
     * @brief getThreatName GETTER
     * @return the threat name
     */
    QString getThreatName();
    /**
     * @brief getThreatType
     * @return
     */
    QString getThreatLocation();
};

#endif // THREATINFO_HPP
