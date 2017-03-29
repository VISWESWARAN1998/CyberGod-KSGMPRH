#pragma once

class RecoveryPanel : public wxWindow
{
protected:
    wxThread* currentThread;
    wxPanel* scanPanel;

    wxTextCtrl* srcLocationEdit;
    wxTextCtrl* dstLocationEdit;
    wxButton* startButton;
    wxStaticText* statusLabel;

    wxStaticText* pathLabel;
    wxStaticText* pathText;

    wxStaticText* filesCountLabel;
    wxStaticText* filesCountText;
    wxStaticText* recoveredCountLabel;
    wxStaticText* recoveredCountText;
    wxStaticText* errorLabel;
    
    wxCriticalSection cs;
    int stopFlag;
    bool inProgress;

    int fileCount;
    int recoveredCount;

    void OnStartButton(wxCommandEvent& event);

    static void OnRecoveryFile(void* context, const wchar_t* path, unsigned long long size, const wchar_t* hash, int notificationType);
    static void OnStatus(void* context, const wchar_t* status);
    static void OnError(void* context, const wchar_t* errorText, int errorType);
    static void OnRecoveryFinish(void* context);
    static bool IsProcessStopped(void* context);

    void OnGUIStatus(wxThreadEvent& event);
    void OnGUIError(wxThreadEvent& event);
    void OnGUIRecoveryFinish(wxThreadEvent& event);
    void OnGUIRecoveryFile(wxThreadEvent& event);

    void Wait();
public:    
    RecoveryPanel(wxFrame* parent);
    ~RecoveryPanel();

    void CreateChildControls();

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    void Stop();

    DECLARE_EVENT_TABLE()
};

