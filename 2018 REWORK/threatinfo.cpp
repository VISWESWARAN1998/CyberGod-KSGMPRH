// SWAMI KARUPPASWAMI THUNNAI
#include "threatinfo.hpp"

ThreatInfo::ThreatInfo()
{

}

ThreatInfo::ThreatInfo(QString threatName, QString threatLocation)
{
    this->threatName = threatName;
    this->threatLocation = threatLocation;
}


QString ThreatInfo::getThreatName()
{
    return threatName;
}

QString ThreatInfo::getThreatLocation()
{
    return threatLocation;
}
