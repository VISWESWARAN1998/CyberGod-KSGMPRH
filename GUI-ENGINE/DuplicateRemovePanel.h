#pragma once

#include "MalwareOperationalThread.h"
#include "OperationalPanel.h"

class DuplicateRemovePanel : public OperationalPanel
{    
    wxTextCtrl* locationEdit;
    wxButton* startButton;
    wxButton* cleanButton;

    int fileCount;
    int duplicateCount;

    wxStaticText* statusLabel;
    wxStaticText* errorLabel;
    wxStaticText* pathLabel;
    wxStaticText* pathText;
    wxStaticText* fileSizeLabel;
    wxStaticText* fileSizeText;
    wxStaticText* filesCountLabel;
    wxStaticText* filesCountText;
    wxStaticText* duplicatedCountLabel;
    wxStaticText* duplicatedCountText;

    wxCheckListBox* checkListBox;
    wxStaticText* szSelectedDirText;
    wxStaticText* szSelectedFileText;
    wxButton* returnButton;
    wxButton* removeButton;

    static void OnStatus(void* context, const wchar_t* status);
    static void OnError(void* context, const wchar_t* errorText, int errorType);
    static void OnScanFinish(void* context);
    static void OnNewFile(void* context, const wchar_t* path, unsigned long long size, const wchar_t* hash, int notificationType);
    static void OnDeleteFinish(void* context);
    static void OnDeleteFile(void* context, int index);

    void OnGUIStatus(wxThreadEvent& event);
    void OnGUIError(wxThreadEvent& event);
    void OnGUIScanFinish(wxThreadEvent& event);
    void OnGUIDeleteFinish(wxThreadEvent& event);
    void OnGUINewFile(wxThreadEvent& event);
    void OnGUIDeleteFile(wxThreadEvent& event);

    void OnStartButton(wxCommandEvent& event);
    void OnCleanButton(wxCommandEvent& event);
    void OnReturnButton(wxCommandEvent& event);
    void OnRemoveButton(wxCommandEvent& event);
    void OnSelectedFileToDelete(wxCommandEvent& event);
public:
    DuplicateRemovePanel(wxFrame* parent);
    ~DuplicateRemovePanel();

    void CreateChildControls();

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void OnClose(wxCloseEvent & evt);

    void render(wxDC& dc);

    DECLARE_EVENT_TABLE()    
};
