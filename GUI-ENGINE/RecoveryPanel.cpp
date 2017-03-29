#include <wx/wxprec.h>
#include <wx/sizer.h>

#include "RecoveryPanel.h"

#include "DuplicateRemovePanel.h"

#include "Engine\recovery.h"

#include "NewFileEventData.h"
#include "ThreadEvents.h"


class RecoveryThread : public MalwareOperationalThread
{    
    RecoveryPanel* panel;
    
    MalwareScan_OnNewDupFile OnRecoveryFile;
    void* OnRecoveryFileContext;
    MalwareScan_OnStatus OnStatus;
    void* OnStatusContext;

    std::wstring drive_letter;
    std::wstring recovery_location;

public:
    RecoveryThread(RecoveryPanel* panel, std::wstring drive_letter, std::wstring recovery_location);

    virtual void *Entry();
    void SetOnStatus(MalwareScan_OnStatus OnStatus, void* OnStatusContext);
    void SetOnRecoveryFile(MalwareScan_OnNewDupFile OnRecoveryFile, void* OnRecoveryFileContext);
};

RecoveryThread::RecoveryThread(RecoveryPanel* panel, std::wstring drive_letter, std::wstring recovery_location)
{
    this->panel = panel;
    this->drive_letter = drive_letter;
    this->recovery_location = recovery_location;
    this->OnRecoveryFile = NULL;
    this->OnRecoveryFileContext = NULL;
    this->OnStatus = NULL;
    this->OnStatusContext = NULL;
}

void * RecoveryThread::Entry()
{   
    Recovery<std::wstring> constructor(OnStatus, OnStatusContext, OnError, OnErrorContext, isStopped, IsStoppedContext);
    Recovery<std::wstring> recover(drive_letter, recovery_location, OnStatus, OnStatusContext, OnError, OnErrorContext, OnRecoveryFile, OnRecoveryFileContext, isStopped, IsStoppedContext);
    recover.end();

    OnFinish(OnFinishContext);
    return NULL;
}

void RecoveryThread::SetOnStatus(MalwareScan_OnStatus OnStatus, void* OnStatusContext)
{
    this->OnStatus = OnStatus;
    this->OnStatusContext = OnStatusContext;
}

void RecoveryThread::SetOnRecoveryFile(MalwareScan_OnNewDupFile OnRecoveryFile, void* OnRecoveryFileContext)
{
    this->OnRecoveryFile = OnRecoveryFile;
    this->OnRecoveryFileContext = OnRecoveryFileContext;
}

BEGIN_EVENT_TABLE(RecoveryPanel, wxPanel)
// catch paint events
// EVT_PAINT(RecoveryPanel::paintEvent)
END_EVENT_TABLE()

RecoveryPanel::RecoveryPanel(wxFrame* parent) : wxWindow(parent, wxID_ANY)
{
    inProgress = false;

    Connect(EVT_MALWARE_SCAN_STATUS, wxThreadEventHandler(RecoveryPanel::OnGUIStatus));
    Connect(EVT_MALWARE_SCAN_ERROR, wxThreadEventHandler(RecoveryPanel::OnGUIError));
    Connect(EVT_MALWARE_SCAN_FINISH, wxThreadEventHandler(RecoveryPanel::OnGUIRecoveryFinish));
    Connect(EVT_RECOVERY_FILE, wxThreadEventHandler(RecoveryPanel::OnGUIRecoveryFile));
}

RecoveryPanel::~RecoveryPanel()
{
    Wait();

    Disconnect(EVT_MALWARE_SCAN_STATUS, wxThreadEventHandler(RecoveryPanel::OnGUIStatus));
    Disconnect(EVT_MALWARE_SCAN_ERROR, wxThreadEventHandler(RecoveryPanel::OnGUIError));
    Disconnect(EVT_MALWARE_SCAN_FINISH, wxThreadEventHandler(RecoveryPanel::OnGUIRecoveryFinish));
    Disconnect(EVT_RECOVERY_FILE, wxThreadEventHandler(RecoveryPanel::OnGUIRecoveryFile));
}

void RecoveryPanel::paintEvent(wxPaintEvent & evt)
{

}

void RecoveryPanel::paintNow()
{

}

void RecoveryPanel::render(wxDC& dc)
{

}

void RecoveryPanel::CreateChildControls()
{
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    verticalSizer->Add(horizontalSizer, 1, wxEXPAND);
    SetSizer(verticalSizer);

    scanPanel = new wxPanel(this);
    horizontalSizer->Add(scanPanel, 1, wxEXPAND);

    scanPanel->SetBackgroundColour(wxColor(252, 250, 245));


    wxStaticText* srcLocationText = new wxStaticText(scanPanel, wxID_ANY, "Drive Letter: ", wxPoint(20, 20));
    wxFont font = srcLocationText->GetFont();
    wxFont boldFont;
    boldFont.Create(font.GetPixelSize(), font.GetFamily(), wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    srcLocationText->SetFont(boldFont);

    wxStaticText* dstLocationText = new wxStaticText(scanPanel, wxID_ANY, "Destination: ", wxPoint(20, 40));
    dstLocationText->SetFont(boldFont);
    
    srcLocationEdit = new wxTextCtrl(scanPanel, 1001, wxEmptyString, wxPoint(100, 20), wxSize(320, 16), wxBORDER_NONE);    
    dstLocationEdit = new wxTextCtrl(scanPanel, 1003, wxEmptyString, wxPoint(100, 40), wxSize(320, 16), wxBORDER_NONE);
    
    errorLabel = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(20, 400));
    errorLabel->SetForegroundColour(wxColor(255, 0, 0));

    startButton = new wxButton(scanPanel, 1011, "Start", wxPoint(80, 62));

    statusLabel = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(20, 100));
    statusLabel->SetFont(boldFont);
    statusLabel->Hide();
    pathLabel = new wxStaticText(scanPanel, wxID_ANY, "Path: ", wxPoint(20, 130));
    pathLabel->SetFont(boldFont);
    pathLabel->Hide();

    pathText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(105, 130), wxSize(655, 15), wxST_ELLIPSIZE_MIDDLE);
    pathText->Hide();    

    filesCountLabel = new wxStaticText(scanPanel, wxID_ANY, "Scanned Files: ", wxPoint(20, 200));
    filesCountLabel->SetFont(boldFont);
    filesCountText = new wxStaticText(scanPanel, wxID_ANY, "0", wxPoint(227, 200), wxSize(60, 16), wxALIGN_RIGHT);

    recoveredCountLabel = new wxStaticText(scanPanel, wxID_ANY, "Recovered Files: ", wxPoint(20, 220));
    recoveredCountLabel->SetFont(boldFont);
    recoveredCountText = new wxStaticText(scanPanel, wxID_ANY, "0", wxPoint(227, 220), wxSize(60, 16), wxALIGN_RIGHT);    

    filesCountLabel->Hide();
    filesCountText->Hide();
    recoveredCountLabel->Hide();
    recoveredCountText->Hide();

    Bind(wxEVT_BUTTON, &RecoveryPanel::OnStartButton, this, 1011);
}

void RecoveryPanel::OnRecoveryFile(void* context, const wchar_t* path, unsigned long long size, const wchar_t* hash, int notificationType)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_RECOVERY_FILE);
    NewFileEventData* obj = new NewFileEventData();

    obj->current_path = path;    
    obj->size = size;

    evt->SetEventObject(obj);
    wxQueueEvent(handler, evt);
}

void RecoveryPanel::OnStatus(void* context, const wchar_t* status)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_STATUS);
    evt->SetString(status);
    wxQueueEvent(handler, evt);
}

void RecoveryPanel::OnError(void* context, const wchar_t* errorText, int errorType)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_ERROR);
    evt->SetString(errorText);
    evt->SetInt(errorType);
    wxQueueEvent(handler, evt);
}

void RecoveryPanel::OnRecoveryFinish(void* context)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;
    ((RecoveryPanel*)context)->inProgress = false;
    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_FINISH);
    wxQueueEvent(handler, evt);
}

void RecoveryPanel::OnStartButton(wxCommandEvent& event)
{
    if (!inProgress)
    {
        startButton->SetLabelText("Stop");
        
        filesCountLabel->Hide();
        filesCountText->Hide();
        recoveredCountText->Hide();
        recoveredCountLabel->Hide();
        
        inProgress = true;

        stopFlag = 0;
        fileCount = 0;
        recoveredCount = 0;

        std::wstring drive_letter, recovery_location;

        drive_letter = srcLocationEdit->GetValue().wc_str();
        recovery_location = dstLocationEdit->GetValue().wc_str();

        RecoveryThread* scanThread = new RecoveryThread(this, drive_letter, recovery_location);
        scanThread->SetOnRecoveryFile(OnRecoveryFile, this);
        scanThread->SetOnStatus(OnStatus, this);
        scanThread->SetOnError(OnError, this);
        scanThread->SetOnFinish(OnRecoveryFinish, this);
        scanThread->SetIsStopped(IsProcessStopped, this);
        
        currentThread = scanThread;
        currentThread->Run();
    }
    else
    {
        Stop();
    }
}

void RecoveryPanel::Wait()
{
    if (currentThread)
    {
        Stop();
        while (inProgress)
        {
            wxMilliSleep(1);
        }
    }
}

void RecoveryPanel::Stop()
{
    cs.Enter();
    stopFlag = 1;
    cs.Leave();
}

bool RecoveryPanel::IsProcessStopped(void* context)
{
    if (context)
    {
        RecoveryPanel* panel = (RecoveryPanel*)context;
        panel->cs.Enter();
        bool stopped = (panel->stopFlag != 0);
        panel->cs.Leave();
        return stopped;
    }
    return false;
}

void RecoveryPanel::OnGUIStatus(wxThreadEvent& event)
{
    wxString statusString = event.GetString();
    statusLabel->SetLabel(statusString);
    statusLabel->Show();
}

void RecoveryPanel::OnGUIError(wxThreadEvent& event)
{
    wxString errorString = event.GetString();
    int errorType = event.GetInt();
    errorLabel->SetLabel(errorString);
    errorLabel->Show();
}

void RecoveryPanel::OnGUIRecoveryFinish(wxThreadEvent& event)
{
    startButton->SetLabelText("Start");

    pathLabel->Hide();    
    pathText->Hide();    

    inProgress = false;
    currentThread = NULL;

    if (IsProcessStopped(this))
        wxMessageBox("Stopped");
    else
        wxMessageBox("Finished");
}

void RecoveryPanel::OnGUIRecoveryFile(wxThreadEvent& event)
{
    NewFileEventData* obj = (NewFileEventData*)event.GetEventObject();

    pathText->Show();
    pathLabel->Show();

    pathText->SetLabel(obj->current_path);

    fileCount++;

    if (obj->size == 1)
    {
        recoveredCount++;
    }
    
    char countText[128];
    sprintf(countText, "%d", fileCount);
    filesCountLabel->Show();
    filesCountText->Show();
    filesCountText->SetLabel(countText);

    sprintf(countText, "%d", recoveredCount);
    recoveredCountLabel->Show();
    recoveredCountText->Show();
    recoveredCountText->SetLabel(countText);

    delete obj;
}
