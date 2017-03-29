#pragma once

#include "OperationalPanel.h"

class USBScanPanel : public OperationalPanel
{    
    wxButton* startButton;
    wxButton* cleanButton;
    wxButton* findButton;

    wxStaticText* usdDrivesText;

    wxStaticText* pathText;
    wxStaticText* extensionText;
    wxStaticText* hashText;

    wxStaticText* filesCountText;
    wxStaticText* scheduledCountText;
    wxStaticText* idendifiedCountText;
    wxStaticText* packedCountText;
    wxStaticText* scannedOnPCText;

    wxStaticText* pathLabel;
    wxStaticText* extensionLabel;
    wxStaticText* hashLabel;
    wxStaticText* statusLabel;
    wxStaticText* errorLabel;
    wxStaticText* filesCountLabel;
    wxStaticText* scheduledCountLabel;
    wxStaticText* idendifiedCountLabel;
    wxStaticText* packedCountLabel;
    wxStaticText* scannedOnPCLabel;

    wxCheckListBox* checkListBox;
    wxButton* returnButton;
    wxButton* removeButton;
    wxStaticText* szSelectedDirText;
    wxStaticText* szSelectedFileText;

    int fileCount;
    int scheduledCount;
    int identifiedCount;
    int packedCount;
    int scannedForPCCount;

    void OnStartButton(wxCommandEvent& event);
    void OnCleanButton(wxCommandEvent& event);
    void OnReturnButton(wxCommandEvent& event);
    void OnRemoveButton(wxCommandEvent& event);
    void OnFindButton(wxCommandEvent& event);
    void OnSelectedFileToDelete(wxCommandEvent& event);
    void OnGUIDeleteFile(wxThreadEvent& event);
    void OnGUIDeleteFinish(wxThreadEvent& event);
    
    static void OnNewFile(void* context, const wchar_t* path, const wchar_t* extension, const wchar_t* hash);    
    static void OnMalicious(void* context, const wchar_t* path, int type);
    static void OnStatus(void* context, const wchar_t* status);
    static void OnError(void* context, const wchar_t* errorText, int errorType);
    static void OnScanFinish(void* context);
    static void OnDeleteFile(void* context, int index);
    static void OnDeleteFinish(void* context);
       
    void OnGUIStatus(wxThreadEvent& event);
    void OnGUIError(wxThreadEvent& event);
    void OnGUIScanFinish(wxThreadEvent& event);
    void OnGUINewFile(wxThreadEvent& event);    
    void OnGUISMalicious(wxThreadEvent& event);    
public:
    USBScanPanel(wxFrame* parent);
    ~USBScanPanel();

    void CreateChildControls();
    void Rescan();

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void OnClose(wxCloseEvent & evt);

    void render(wxDC& dc);

    DECLARE_EVENT_TABLE()
};

