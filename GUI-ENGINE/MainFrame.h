#pragma once

#include "TopLargeButton.h"
#include "Logo.h"

#include "MalwareScanPanel.h"
#include "USBScanPanel.h"
#include "DuplicateRemovePanel.h"
#include "RecoveryPanel.h"
#include "PluginPanel.h"
#include "SettingsPanel.h"

class MainFrame : public wxFrame
{
    TopLargeButton* malwareScanButton;
    TopLargeButton* duplicateRemoveButton;
    TopLargeButton* recoveryButton;
    TopLargeButton* pluginButton;
    TopLargeButton* settingsButton;
    TopLargeButton* quickScanButton;
    TopLargeButton* usbScanButton;

    wxStaticText* currentTab;

    MalwareScanPanel* malwareScanPanel;
    USBScanPanel* usbScanPanel;
    MalwareScanPanel* quickScanPanel;
    DuplicateRemovePanel* duplicateRemovePanel;
    RecoveryPanel* recoveryPanel;
    PluginPanel* pluginPanel;
    SettingsPanel* settingsPanel;
public:
    MainFrame();
    ~MainFrame();

    void OnMalwareScan();
    void OnDuplicateFiles();
    void OnUSBScan();
    void OnQuickScan();
    void OnRecovery();
    void OnSettings();
    void OnPlugin();
private:

    wxDECLARE_EVENT_TABLE();

    void CreateButtons(wxBoxSizer* sizer);
    void CreateLogo(wxBoxSizer* sizer);
};
