#include <wx/wxprec.h>
#include <wx/gdicmn.h>
#include <wx/xrc/xmlres.h>

#include "MainFrame.h"
#include "Logo.h"
#include "Commands.h"



BEGIN_EVENT_TABLE(MainFrame, wxFrame)

END_EVENT_TABLE();


MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "CyberGod KSGMPRH", wxPoint(-1, -1), wxSize(800, 575),
        wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION /*| wxRESIZE_BORDER */ | wxCLIP_CHILDREN)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* captionSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

    CreateButtons(buttonsSizer);
    CreateLogo(buttonsSizer);

    sizer->Add(buttonsSizer, 0);
    sizer->Add(captionSizer, 1, wxEXPAND);
    sizer->Add(bottomSizer, 24, wxEXPAND);
    SetSizer(sizer);

    wxPanel* panel = new wxPanel(this);
    //wxPanel* leftPanel = new wxPanel(this);
    //leftPanel->SetMinSize(wxSize(30, 26));
    //captionSizer->Add(leftPanel);
    panel->SetBackgroundColour(wxColor(0, 0, 0));
    captionSizer->Add(panel, 1, wxEXPAND | wxLEFT | wxRIGHT);

    currentTab = new wxStaticText(panel, wxID_ANY, "", wxPoint(2, 2));
    currentTab->SetForegroundColour(wxColor(255, 255, 255));
    wxFont font = currentTab->GetFont();
    wxFont boldFont;
    boldFont.Create(12, font.GetFamily(), wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    currentTab->SetFont(boldFont);

    malwareScanPanel = new MalwareScanPanel(this, 0);    
    bottomSizer->Add(malwareScanPanel, 1, wxEXPAND | wxLEFT | wxRIGHT);
    malwareScanPanel->CreateChildControls();
    malwareScanPanel->Hide();

    duplicateRemovePanel = new DuplicateRemovePanel(this);
    //duplicateRemovePanel->SetBackgroundColour(wxColor(220, 200, 100));    
    bottomSizer->Add(duplicateRemovePanel, 1, wxEXPAND | wxLEFT | wxRIGHT);
    duplicateRemovePanel->CreateChildControls();
    duplicateRemovePanel->Hide();
    
    recoveryPanel = new RecoveryPanel(this);
    bottomSizer->Add(recoveryPanel, 1, wxEXPAND | wxLEFT | wxRIGHT);
    recoveryPanel->CreateChildControls();
    recoveryPanel->Hide();

	pluginPanel = new PluginPanel(this);
	pluginPanel->CreateChildControls();
	bottomSizer->Add(pluginPanel, 1, wxEXPAND | wxLEFT | wxRIGHT);
	pluginPanel->Hide();

	settingsPanel = new SettingsPanel(this);
	bottomSizer->Add(settingsPanel, 1, wxEXPAND | wxLEFT | wxRIGHT);
	settingsPanel->Hide();
    

    usbScanPanel = new USBScanPanel(this);
    bottomSizer->Add(usbScanPanel, 1, wxEXPAND | wxLEFT | wxRIGHT);
    usbScanPanel->CreateChildControls();
    usbScanPanel->Hide();

    quickScanPanel = new MalwareScanPanel(this, 1);
    bottomSizer->Add(quickScanPanel, 1, wxEXPAND | wxLEFT | wxRIGHT);
    quickScanPanel->CreateChildControls();
    quickScanPanel->Hide();   

    OnMalwareScan();
}

MainFrame::~MainFrame()
{
    int x = 1;
}


// For now we are commenting out the plugins and settings
void MainFrame::CreateButtons(wxBoxSizer* sizer)
{        
    
    malwareScanButton = new TopLargeButton(this, _T("System Scan"), ID_SCAN,"buttons\\icon 1.png","buttons\\icon 1.png");// , _T("Full-Scan.png"), _T("Full-Scan selected.png"));
    duplicateRemoveButton = new TopLargeButton(this, _T("Duplicate Remove"), ID_DUPLICATE_REMOVE, "buttons\\icon 4.png", "buttons\\icon 4.png");
    recoveryButton = new TopLargeButton(this, _T("Recovery"), ID_RECOVERY, "buttons\\icon 5.png", "buttons\\icon 5.png");
    //pluginButton = new TopLargeButton(this, _T("Plugin"), ID_PLUGIN);
    //settingsButton = new TopLargeButton(this, _T("Settings"), ID_SETTINS);
    usbScanButton = new TopLargeButton(this, _T("USB Scan"), ID_USB_SCAN, "buttons\\icon 3.png", "buttons\\icon 3.png");
    quickScanButton = new TopLargeButton(this, _T("Quick Scan"), ID_QUICK_SCAN, "buttons\\icon 2.png", "buttons\\icon 2.png");

    Logo* logo = new Logo(this);

    wxBoxSizer* spaceSizer = new wxBoxSizer(wxHORIZONTAL);
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColor(0, 0, 0, 255));

    sizer->Add(malwareScanButton, 0, wxLEFT);
    sizer->Add(duplicateRemoveButton, 0, wxLEFT);
    sizer->Add(recoveryButton, 0, wxLEFT);        
    sizer->Add(usbScanButton, 0, wxLEFT);
    sizer->Add(quickScanButton, 0, wxLEFT);
    //sizer->Add(pluginButton, 0, wxLEFT);
    //sizer->Add(settingsButton, 0, wxLEFT);

    panel->SetMinSize(wxSize(270, 30));    

    sizer->Add(panel, 1, wxEXPAND); //| wxLEFT | wxRIGHT, 8);
    sizer->Add(logo, 0, wxRIGHT);    
}

void MainFrame::CreateLogo(wxBoxSizer* sizer)
{

}

void MainFrame::OnMalwareScan()
{        
    duplicateRemovePanel->Hide();
    quickScanPanel->Hide();
    usbScanPanel->Hide();
    recoveryPanel->Hide();
    pluginPanel->Hide();
    settingsPanel->Hide();
    malwareScanPanel->Show();
    currentTab->SetLabel("System Malware Scan");
    Layout();    
}

void MainFrame::OnDuplicateFiles()
{
    malwareScanPanel->Hide();
    quickScanPanel->Hide();
    usbScanPanel->Hide();
    recoveryPanel->Hide();
    pluginPanel->Hide();
    settingsPanel->Hide();
    duplicateRemovePanel->Show();
    currentTab->SetLabel("Duplicate File Remover");
    Layout();
}

void MainFrame::OnQuickScan()
{
    duplicateRemovePanel->Hide();    
    malwareScanPanel->Hide();
    usbScanPanel->Hide();
    recoveryPanel->Hide();
    pluginPanel->Hide();
    settingsPanel->Hide();
    quickScanPanel->Show();
    currentTab->SetLabel("Quick Malware Scan");
    Layout();
}

void MainFrame::OnUSBScan()
{
    duplicateRemovePanel->Hide();
    malwareScanPanel->Hide();
    quickScanPanel->Hide();
    recoveryPanel->Hide();
    pluginPanel->Hide();
    settingsPanel->Hide();
    usbScanPanel->Rescan();
    usbScanPanel->Show();
    currentTab->SetLabel("USB Malware Scan");
    Layout();
}

void MainFrame::OnRecovery()
{
    malwareScanPanel->Hide();
    quickScanPanel->Hide();
    usbScanPanel->Hide();
    duplicateRemovePanel->Hide();
    pluginPanel->Hide();
    settingsPanel->Hide();
    recoveryPanel->Show();
    currentTab->SetLabel("Recovery");
    Layout();
}

void MainFrame::OnSettings()
{
    malwareScanPanel->Hide();
    quickScanPanel->Hide();
    usbScanPanel->Hide();
    duplicateRemovePanel->Hide();
    pluginPanel->Hide();
    recoveryPanel->Hide();
    settingsPanel->Show();
    currentTab->SetLabel("Settings");
    Layout();
}

void MainFrame::OnPlugin()
{
    malwareScanPanel->Hide();
    quickScanPanel->Hide();
    usbScanPanel->Hide();
    duplicateRemovePanel->Hide();
    settingsPanel->Hide();
    recoveryPanel->Hide();
    pluginPanel->FillPluginList();
    pluginPanel->Show();
    currentTab->SetLabel("Plugins");
    Layout();
}