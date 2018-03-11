// SWAMI KARUPPASWAMI THUNNAI

#include "cybergod.hpp"
#include "customscan.hpp"
#include "aboutus.hpp"
#include "thirdparty.hpp"
#include "shortcutvirusremover.hpp"
#include "rubberduckydetector.hpp"

//===============================================================
//                  MENU ITMES CLICKED EVENTS
//===============================================================

// Information menu
void CyberGod::on_actionAbout_us_triggered()
{
    AboutUs about;
    about.setModal(true);
    about.setWindowTitle("About CyberGod KSGMPRH");
    about.exec();
}

void CyberGod::on_actionThird_party_notices_triggered()
{
    ThirdParty party;
    party.setModal(true);
    party.setWindowTitle(tr("Third Party License"));
    party.exec();
}

// Scan menu
void CyberGod::on_actionCustom_Scan_triggered()
{
    CustomScan scan;
    scan.setModal(true);
    scan.setWindowTitle("CyberGod KSGMPRH - Custom Scan");
    scan.exec();
}

// Tools menu
void CyberGod::on_actionFix_shortcut_virus_triggered()
{
    ShortCutVirusRemover remover;
    remover.setModal(true);
    remover.setWindowTitle("Shortcut virus remover");
    remover.exec();
}

void CyberGod::on_actionDetect_Rubber_Ducky_triggered()
{
    RubberDuckyDetector detector;
    detector.setModal(true);
    detector.setWindowTitle("Rubber Ducky Detector");
    detector.exec();
}

