#include <list>

#include <boost\filesystem.hpp>

#include <wx\wxprec.h>
#include <wx\sizer.h>

#include "MalwareOperationalThread.h"
#include "NewFileEventData.h"

#include "ThreadEvents.h"
#include "USBScanPanel.h"

#include "Engine\utilities.h"
#include "Engine\usb.h"

BEGIN_EVENT_TABLE(USBScanPanel, wxPanel)
// catch paint events
// EVT_PAINT(USBScanPanel::paintEvent)
END_EVENT_TABLE()


class USBScanThread : public MalwareOperationalThread
{
    USBScanPanel* panel;    

    MalwareScan_OnNewFile OnNewFile;
    void* OnNewFileContext;

    MalwareScan_OnMalicious OnMalicious;
    void* OnMaliciousContext;

    MalwareScan_OnStatus OnStatus;
    void* OnStatusContext;
public:
    USBScanThread(USBScanPanel* panel);

    virtual void *Entry();

    void SetOnNewFile(MalwareScan_OnNewFile OnNewFile, void* OnNewFileContext);
    void SetOnStatus(MalwareScan_OnStatus OnStatus, void* OnStatusContext);

    void SetOnMalicious(MalwareScan_OnMalicious OnMalicious, void* OnMaliciousContext);    
};

class USBDeleteThread : public MalwareOperationalThread
{
    USBScanPanel* panel;
    wxCheckListBox* checkListBox;

    MalwareScan_OnDeleteFile OnDeleteFile;
    void* OnDeleteContext;
public:
    USBDeleteThread(USBScanPanel* panel, wxCheckListBox* checkListBox);
    void SetOnDeleteFile(MalwareScan_OnDeleteFile OnDeleteFile, void* OnDeleteContext);

    virtual void *Entry();
};

USBScanThread::USBScanThread(USBScanPanel* panel) : MalwareOperationalThread()
{
    this->panel = panel;
    OnNewFile = NULL;
    OnNewFileContext = NULL;
    OnMalicious = NULL;
    OnMaliciousContext = NULL;    
    OnStatus = NULL;
    OnStatusContext = NULL;    
}

void USBScanThread::SetOnNewFile(MalwareScan_OnNewFile OnNewFile, void* OnNewFileContext)
{
    this->OnNewFile = OnNewFile;
    this->OnNewFileContext = OnNewFileContext;
}

void USBScanThread::SetOnMalicious(MalwareScan_OnMalicious OnMalicious, void* OnMaliciousContext)
{
    this->OnMalicious = OnMalicious;
    this->OnMaliciousContext = OnMaliciousContext;
}

void USBScanThread::SetOnStatus(MalwareScan_OnStatus OnStatus, void* OnStatusContext)
{
    this->OnStatus = OnStatus;
    this->OnStatusContext = OnStatusContext;
}

void* USBScanThread::Entry()
{
    for (char d = 'A'; d <= 'Z'; d++)
    {
        char drive[] = "?:\\";
        drive[0] = d;

        if (get_drive_status(drive) == 2)
        {
            USBScan<std::wstring> usb;
            usb.SetIsStopped(isStopped, IsStoppedContext);
            usb.SetOnError(OnError, OnErrorContext);
            usb.SetOnNewFile(OnNewFile, OnNewFileContext);
            usb.SetOnStatus(OnStatus, OnStatusContext);
            usb.SetOnMalicious(OnMalicious, OnMaliciousContext);
            usb.initialize(drive);
        }
    }

    OnFinish(OnFinishContext);

    return NULL;
}

USBDeleteThread::USBDeleteThread(USBScanPanel* panel, wxCheckListBox* checkListBox) : MalwareOperationalThread()
{
    this->panel = panel;
    this->checkListBox = checkListBox;

    this->OnDeleteFile = NULL;
    this->OnDeleteContext = NULL;
}

void USBDeleteThread::SetOnDeleteFile(MalwareScan_OnDeleteFile OnDeleteFile, void* OnDeleteContext)
{
    this->OnDeleteFile = OnDeleteFile;
    this->OnDeleteContext = OnDeleteContext;
}

void* USBDeleteThread::Entry()
{

    for (int itemIndex = checkListBox->GetCount(); itemIndex > 0; itemIndex--)
    {
        if (checkListBox->IsChecked(itemIndex - 1))
        {
            wxString name = checkListBox->GetItem(itemIndex - 1)->GetName();
            wchar_t* ww = (wchar_t*)(name.c_str().AsWChar());
			_tremove(ww); // removing file itself
            OnDeleteFile(OnDeleteContext, itemIndex - 1);
        }
    }

    OnFinish(OnFinishContext);
    return NULL;
}



USBScanPanel::USBScanPanel(wxFrame* parent) : OperationalPanel(parent)
{    
    Connect(EVT_MALWARE_SCAN_STATUS, wxThreadEventHandler(USBScanPanel::OnGUIStatus));
    Connect(EVT_MALWARE_SCAN_ERROR, wxThreadEventHandler(USBScanPanel::OnGUIError));
    Connect(EVT_MALWARE_SCAN_FINISH, wxThreadEventHandler(USBScanPanel::OnGUIScanFinish));
    Connect(EVT_MALWARE_SCAN_NEWFILE, wxThreadEventHandler(USBScanPanel::OnGUINewFile));
    Connect(EVT_MALWARE_SCAN_FOUND, wxThreadEventHandler(USBScanPanel::OnGUISMalicious));
    Connect(EVT_MALWARE_DELETE_FILE, wxThreadEventHandler(USBScanPanel::OnGUIDeleteFile));
    Connect(EVT_MALWARE_DELETE_FINISH, wxThreadEventHandler(USBScanPanel::OnGUIDeleteFinish));        
}


USBScanPanel::~USBScanPanel()
{
    Wait();

    Disconnect(EVT_MALWARE_SCAN_STATUS, wxThreadEventHandler(USBScanPanel::OnGUIStatus));
    Disconnect(EVT_MALWARE_SCAN_ERROR, wxThreadEventHandler(USBScanPanel::OnGUIError));
    Disconnect(EVT_MALWARE_SCAN_FINISH, wxThreadEventHandler(USBScanPanel::OnGUIScanFinish));
    Disconnect(EVT_MALWARE_SCAN_NEWFILE, wxThreadEventHandler(USBScanPanel::OnGUINewFile));
    Disconnect(EVT_MALWARE_SCAN_FOUND, wxThreadEventHandler(USBScanPanel::OnGUISMalicious));
    Disconnect(EVT_MALWARE_DELETE_FILE, wxThreadEventHandler(USBScanPanel::OnGUIDeleteFile));
    Disconnect(EVT_MALWARE_DELETE_FINISH, wxThreadEventHandler(USBScanPanel::OnGUIDeleteFinish));
}

void USBScanPanel::CreateChildControls()
{
    CreatePanels();

    startButton = new wxButton(scanPanel, 1002, "Start", wxPoint(30, 42));

    wxStaticText* locationText = new wxStaticText(scanPanel, wxID_ANY, "USB Drives: ", wxPoint(20, 20));
    wxFont font = locationText->GetFont();    
    wxFont boldFont;
    boldFont.Create(font.GetPixelSize(), font.GetFamily(), wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    locationText->SetFont(boldFont);

    usdDrivesText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(90, 20));

    statusLabel = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(20, 100));
    statusLabel->SetFont(boldFont);
    statusLabel->Hide();

    pathLabel = new wxStaticText(scanPanel, wxID_ANY, "Path: ", wxPoint(20, 130));
    pathLabel->SetFont(boldFont);
    extensionLabel = new wxStaticText(scanPanel, wxID_ANY, "Extension: ", wxPoint(20, 150));
    extensionLabel->SetFont(boldFont);
    hashLabel = new wxStaticText(scanPanel, wxID_ANY, "Hash: ", wxPoint(20, 170));
    hashLabel->SetFont(boldFont);

    pathLabel->Hide();
    extensionLabel->Hide();
    hashLabel->Hide();

    pathText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(105, 130), wxSize(655, 15), wxST_ELLIPSIZE_MIDDLE);
    extensionText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(105, 150));
    hashText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(105, 170));

    pathText->Hide();
    extensionText->Hide();
    hashText->Hide();

    filesCountLabel = new wxStaticText(scanPanel, wxID_ANY, "Scanned Files: ", wxPoint(20, 200));
    filesCountLabel->SetFont(boldFont);

    scheduledCountLabel = new wxStaticText(scanPanel, wxID_ANY, "Scheduled Files: ", wxPoint(20, 220));
    scheduledCountLabel->SetFont(boldFont);

    idendifiedCountLabel = new wxStaticText(scanPanel, wxID_ANY, "Identified Malicious Files: ", wxPoint(20, 250));
    idendifiedCountLabel->SetFont(boldFont);

    packedCountLabel = new wxStaticText(scanPanel, wxID_ANY, "Suspictious Packed Files: ", wxPoint(20, 270));
    packedCountLabel->SetFont(boldFont);

    scannedOnPCLabel = new wxStaticText(scanPanel, wxID_ANY, "Files to be scanned the same in PC: ", wxPoint(20, 290));
    scannedOnPCLabel->SetFont(boldFont);

    filesCountText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(227, 200), wxSize(60, 16), wxALIGN_RIGHT);
    scheduledCountText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(227, 220), wxSize(60, 16), wxALIGN_RIGHT);
    idendifiedCountText = new wxStaticText(scanPanel, wxID_ANY, "00", wxPoint(227, 250), wxSize(60, 16), wxALIGN_RIGHT);
    packedCountText = new wxStaticText(scanPanel, wxID_ANY, "00", wxPoint(227, 270), wxSize(60, 16), wxALIGN_RIGHT);
    scannedOnPCText = new wxStaticText(scanPanel, wxID_ANY, "00", wxPoint(227, 290), wxSize(60, 16), wxALIGN_RIGHT);
            
    //    
    //


    filesCountLabel->Hide();
    scheduledCountLabel->Hide();
    idendifiedCountLabel->Hide();
    packedCountLabel->Hide();
    scannedOnPCText->Hide();

    filesCountText->Hide();
    scheduledCountText->Hide();
    idendifiedCountText->Hide();
    packedCountText->Hide();
    scannedOnPCLabel->Hide();

    cleanButton = new wxButton(scanPanel, 1003, "Clean...", wxPoint(300, 255));
    cleanButton->Hide();

    errorLabel = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(20, 400));
    errorLabel->SetForegroundColour(wxColor(255, 0, 0));

    wxStaticText* checkListBoxLabel = new wxStaticText(deletePanel, wxID_ANY, "List of malicious files:", wxPoint(20, 12));
    checkListBoxLabel->SetFont(boldFont);
    checkListBox = new wxCheckListBox(deletePanel, 2001, wxPoint(20, 30), wxSize(730, 310));
    long style = wxBORDER_NONE | checkListBox->GetWindowStyle();
    checkListBox->SetWindowStyle(style);

    wxStaticText* szSelectedDirLabel = new wxStaticText(deletePanel, wxID_ANY, "Selected Path:", wxPoint(20, 345));
    wxStaticText* szSelectedFileLabel = new wxStaticText(deletePanel, wxID_ANY, "Selected File:", wxPoint(20, 362));
    szSelectedDirLabel->SetFont(boldFont);
    szSelectedFileLabel->SetFont(boldFont);
    szSelectedDirText = new wxStaticText(deletePanel, wxID_ANY, "", wxPoint(110, 345), wxSize(640, 16), wxST_ELLIPSIZE_MIDDLE);
    szSelectedFileText = new wxStaticText(deletePanel, wxID_ANY, "", wxPoint(110, 362), wxSize(640, 16));


    returnButton = new wxButton(deletePanel, 2002, "Return...", wxPoint(20, 396));
    removeButton = new wxButton(deletePanel, 2003, "Remove", wxPoint(20, 396));
    wxSize buttonSize = removeButton->GetSize();
    removeButton->SetPosition(wxPoint(750 - buttonSize.GetWidth(), 396));

            
    Bind(wxEVT_LISTBOX, &USBScanPanel::OnSelectedFileToDelete, this, 2001);

    Bind(wxEVT_BUTTON, &USBScanPanel::OnStartButton, this, 1002);
    Bind(wxEVT_BUTTON, &USBScanPanel::OnCleanButton, this, 1003);
    Bind(wxEVT_BUTTON, &USBScanPanel::OnReturnButton, this, 2002);
    Bind(wxEVT_BUTTON, &USBScanPanel::OnRemoveButton, this, 2003);
}

void USBScanPanel::Rescan()
{
    std::string usdDrives = "";
    for (char d = 'A'; d <= 'Z'; d++)
    {
        char drive[] = "?:\\";
        drive[0] = d;

        if (get_drive_status(drive) == 2)
        {
            usdDrives += drive;
            usdDrives += "; ";
        }
    }

    if (usdDrives.size() == 0)
        usdDrives = "None Found";

    usdDrivesText->SetLabel(wxString(usdDrives.c_str()));
}

void USBScanPanel::OnClose(wxCloseEvent & evt)
{
    // Stop();
}

void USBScanPanel::paintEvent(wxPaintEvent & evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

void USBScanPanel::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

void USBScanPanel::render(wxDC&  dc)
{
}

void USBScanPanel::OnNewFile(void* context, const wchar_t* path, const wchar_t* extension, const wchar_t* hash)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_NEWFILE);
    NewFileEventData* obj = new NewFileEventData();

    obj->current_path = path;
    obj->extension = extension;
    obj->hash = hash;

    evt->SetEventObject(obj);
    wxQueueEvent(handler, evt);
}

void USBScanPanel::OnMalicious(void* context, const wchar_t* path, int type)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_FOUND);
    evt->SetString(path);
    evt->SetInt(type);
    wxQueueEvent(handler, evt);
}

void USBScanPanel::OnStatus(void* context, const wchar_t* status)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_STATUS);
    evt->SetString(status);
    wxQueueEvent(handler, evt);
}

void USBScanPanel::OnError(void* context, const wchar_t* errorText, int errorType)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_ERROR);
    evt->SetString(errorText);
    evt->SetInt(errorType);
    wxQueueEvent(handler, evt);
}

void USBScanPanel::OnScanFinish(void* context)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;
    ((USBScanPanel*)context)->inProgress = false;
    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_FINISH);
    wxQueueEvent(handler, evt);
}

void USBScanPanel::OnCleanButton(wxCommandEvent& event)
{
    scanPanel->Hide();
    deletePanel->Show();
    Layout();
}

void USBScanPanel::OnFindButton(wxCommandEvent& event)
{

}

void USBScanPanel::OnStartButton(wxCommandEvent& event)
{

    if (!inProgress)
    {
        startButton->SetLabelText("Stop");

        scheduledCountLabel->Hide();
        scheduledCountText->Hide();
        filesCountLabel->Hide();
        filesCountText->Hide();
        packedCountText->Hide();
        packedCountLabel->Hide();
        idendifiedCountText->Hide();
        idendifiedCountLabel->Hide();
        scannedOnPCText->Hide();
        scannedOnPCLabel->Hide();

        checkListBox->Clear();
        cleanButton->Hide();

        inProgress = true;

        stopFlag = 0;
        fileCount = 0;
        scheduledCount = 0;
        identifiedCount = 0;
        packedCount = 0;
        scannedForPCCount = 0;
        
        USBScanThread* scanThread = new USBScanThread(this);
        scanThread->SetOnNewFile(OnNewFile, this);
        scanThread->SetOnStatus(OnStatus, this);
        scanThread->SetOnError(OnError, this);
        scanThread->SetOnFinish(OnScanFinish, this);        
        scanThread->SetOnMalicious(OnMalicious, this);
        scanThread->SetIsStopped(IsProcessStopped, this);
        currentThread = scanThread;
        currentThread->Run();        
    }
    else
    {
        Stop();
    }
}

void USBScanPanel::OnGUIStatus(wxThreadEvent& event)
{
    wxString statusString = event.GetString();
    statusLabel->SetLabel(statusString);
    statusLabel->Show();
}

void USBScanPanel::OnGUIError(wxThreadEvent& event)
{
    wxString errorString = event.GetString();
    int errorType = event.GetInt();
    errorLabel->SetLabel(errorString);
    errorLabel->Show();
}

void USBScanPanel::OnGUIScanFinish(wxThreadEvent& event)
{
    startButton->SetLabelText("Start");

    pathLabel->Hide();
    extensionLabel->Hide();
    hashLabel->Hide();
    pathText->Hide();
    extensionText->Hide();
    hashText->Hide();
    
    inProgress = false;
    currentThread = NULL;

    if (identifiedCount > 0 || packedCount > 0)
        cleanButton->Show();

    if (IsProcessStopped(this))
        wxMessageBox("Stopped");
    else
        wxMessageBox("Finished");
}

void USBScanPanel::OnGUINewFile(wxThreadEvent& event)
{
    NewFileEventData* obj = (NewFileEventData*)event.GetEventObject();

    pathText->Show();

    //hashText->Show();

    pathLabel->Show();

    //hashLabel->Show();

    pathText->SetLabel(obj->current_path);
    /*if (obj->extension == "?")
    {
        extensionLabel->Hide();
        extensionText->Hide();
        extensionText->SetLabel("");
    }
    else
    {
        extensionLabel->Show();
        extensionText->Show();
        extensionText->SetLabel(obj->extension);
    }
    hashText->SetLabel(obj->hash);
    */

    fileCount++;

    char countText[128];
    sprintf(countText, "%d", fileCount);
    filesCountLabel->Show();
    filesCountText->Show();
    filesCountText->SetLabel(countText);

    delete obj;
}

void USBScanPanel::OnGUISMalicious(wxThreadEvent& event)
{
    wxString pathString = event.GetString();
    int maliciousType = event.GetInt();

    if (maliciousType == MALICIOUS_IDENTIFID)
        identifiedCount++;
    if (maliciousType == MALICIOUS_PACKED)
        packedCount++;
    if (maliciousType == SCANNED_FOR_PC)
        scannedForPCCount++;

    if (maliciousType == MALICIOUS_IDENTIFID || maliciousType == MALICIOUS_PACKED)
        checkListBox->Append(pathString);

    char countText[128];
    sprintf(countText, "%d", identifiedCount);
    idendifiedCountText->Show();
    idendifiedCountLabel->Show();
    idendifiedCountText->SetLabel(countText);

    sprintf(countText, "%d", packedCount);
    packedCountText->Show();
    packedCountLabel->Show();
    packedCountText->SetLabel(countText);  

    sprintf(countText, "%d", scannedForPCCount);
    scannedOnPCText->Show();
    scannedOnPCLabel->Show();
    scannedOnPCText->SetLabel(countText);    
}

void USBScanPanel::OnReturnButton(wxCommandEvent& event)
{
    deletePanel->Hide();
    scanPanel->Show();
    Layout();
}

void USBScanPanel::OnRemoveButton(wxCommandEvent& event)
{
    checkListBox->Enable(false);
    removeButton->Enable(false);
    returnButton->Enable(false);
    szSelectedDirText->SetLabelText("");
    szSelectedFileText->SetLabelText("");

    USBDeleteThread* deleteThread = new USBDeleteThread(this, checkListBox);
    deleteThread->SetOnDeleteFile(OnDeleteFile, this);
    deleteThread->SetOnFinish(OnDeleteFinish, this);
    deleteThread->SetIsStopped(IsProcessStopped, this);
    currentThread = deleteThread;
    currentThread->Run();
}

void USBScanPanel::OnSelectedFileToDelete(wxCommandEvent& event)
{
    int index = event.GetInt();
    wxOwnerDrawn* item = checkListBox->GetItem(index);
    wxString name = item->GetName();

    boost::filesystem::path Path = name;
            
    szSelectedDirText->SetLabelText(Path.parent_path().c_str());
    szSelectedFileText->SetLabelText(Path.filename().c_str());
}


void USBScanPanel::OnDeleteFile(void* context, int index)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_DELETE_FILE);
    evt->SetInt(index);
    wxQueueEvent(handler, evt);
}

void USBScanPanel::OnDeleteFinish(void* context)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;
    ((USBScanPanel*)context)->inProgress = false;
    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_DELETE_FINISH);
    wxQueueEvent(handler, evt);
}

void USBScanPanel::OnGUIDeleteFile(wxThreadEvent& event)
{
    int deleteIndex = event.GetInt();
    checkListBox->Delete(deleteIndex);
}

void USBScanPanel::OnGUIDeleteFinish(wxThreadEvent& event)
{
    checkListBox->Enable(true);
    removeButton->Enable(true);
    returnButton->Enable(true);

    if (checkListBox->GetCount() == 0)
        removeButton->Hide();
}