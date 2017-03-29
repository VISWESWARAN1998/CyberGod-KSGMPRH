#include <list>

#include <boost\filesystem.hpp>

#include <wx/wxprec.h>
#include <wx/sizer.h>

#include "DuplicateRemovePanel.h"

#include "NewFileEventData.h"
#include "ThreadEvents.h"

#include "Engine\utilities.h"
#include "Engine\duplicates.h"

BEGIN_EVENT_TABLE(DuplicateRemovePanel, wxPanel)
END_EVENT_TABLE()

class DuplicateScanThread : public MalwareOperationalThread
{
    std::list<wxString> location;
    DuplicateRemovePanel* panel;
        
    MalwareScan_OnStatus OnStatus;
    void* OnStatusContext;

    MalwareScan_OnNewDupFile OnNewFile;
    void* OnNewFileContext;
       
public:
    DuplicateScanThread(DuplicateRemovePanel* panel, std::list<wxString>& location);

    virtual void *Entry();    
    void SetOnStatus(MalwareScan_OnStatus OnStatus, void* OnStatusContext);
    void SetOnNewFile(MalwareScan_OnNewDupFile OnNewFile, void* OnNewFileContext);
};


class DuplicateDeleteThread : public MalwareOperationalThread
{
    DuplicateRemovePanel* panel;
    wxCheckListBox* checkListBox;

    MalwareScan_OnDeleteFile OnDeleteFile;
    void* OnDeleteContext;
public:
    DuplicateDeleteThread(DuplicateRemovePanel* panel, wxCheckListBox* checkListBox);
    void SetOnDeleteFile(MalwareScan_OnDeleteFile OnDeleteFile, void* OnDeleteContext);

    virtual void *Entry();
};

DuplicateScanThread::DuplicateScanThread(DuplicateRemovePanel* panel, std::list<wxString>& location)
{
    this->panel = panel;
    this->location = location;
}

void* DuplicateScanThread::Entry()
{

    Duplicates<std::wstring> obj(OnStatus, OnStatusContext, OnError, OnErrorContext, isStopped, IsStoppedContext);
    obj.SetOnNewFile(OnNewFile, OnNewFileContext);

    //obj.SetOnScheduled(OnScheduled, OnScheduledContext);
    //obj.SetOnMalicious(OnMalicious, OnMaliciousContext);
    //obj.set_boost_scan(false);

    for (std::list<wxString>::iterator it = location.begin(); it != location.end() && !isStopped(IsStoppedContext); it++)
    {
        obj.scan(it->wc_str());
    }

    obj.find_the_duplicates();

    obj.get_duplicates();
  
    OnFinish(OnFinishContext);
    return NULL;
}

void DuplicateScanThread::SetOnStatus(MalwareScan_OnStatus OnStatus, void* OnStatusContext)
{
    this->OnStatus = OnStatus;
    this->OnStatusContext = OnStatusContext;
}

void DuplicateScanThread::SetOnNewFile(MalwareScan_OnNewDupFile OnNewFile, void* OnNewFileContext)
{
    this->OnNewFile = OnNewFile;
    this->OnNewFileContext = OnNewFileContext;
}

DuplicateDeleteThread::DuplicateDeleteThread(DuplicateRemovePanel* panel, wxCheckListBox* checkListBox) : MalwareOperationalThread()
{
    this->panel = panel;
    this->checkListBox = checkListBox;

    this->OnDeleteFile = NULL;
    this->OnDeleteContext = NULL;
}

void DuplicateDeleteThread::SetOnDeleteFile(MalwareScan_OnDeleteFile OnDeleteFile, void* OnDeleteContext)
{
    this->OnDeleteFile = OnDeleteFile;
    this->OnDeleteContext = OnDeleteContext;
}

void* DuplicateDeleteThread::Entry()
{

    for (int itemIndex = checkListBox->GetCount(); itemIndex > 0; itemIndex--)
    {
        if (checkListBox->IsChecked(itemIndex - 1))
        {
            wxString name = checkListBox->GetItem(itemIndex - 1)->GetName();
            wchar_t* ww = (wchar_t*)(name.c_str().AsWChar());
			//_tremove(ww); // removing file itself
			utilityRemove(ww);
            OnDeleteFile(OnDeleteContext, itemIndex - 1);
        }
    }

    OnFinish(OnFinishContext);
    return NULL;
}


DuplicateRemovePanel::DuplicateRemovePanel(wxFrame* parent)
    : OperationalPanel(parent)
{
    Connect(EVT_MALWARE_SCAN_STATUS, wxThreadEventHandler(DuplicateRemovePanel::OnGUIStatus));
    Connect(EVT_MALWARE_SCAN_ERROR, wxThreadEventHandler(DuplicateRemovePanel::OnGUIError));           
    Connect(EVT_MALWARE_SCAN_NEWFILE, wxThreadEventHandler(DuplicateRemovePanel::OnGUINewFile));
    Connect(EVT_MALWARE_SCAN_FINISH, wxThreadEventHandler(DuplicateRemovePanel::OnGUIScanFinish));
    Connect(EVT_MALWARE_DELETE_FILE, wxThreadEventHandler(DuplicateRemovePanel::OnGUIDeleteFile));
    Connect(EVT_MALWARE_DELETE_FINISH, wxThreadEventHandler(DuplicateRemovePanel::OnGUIDeleteFinish));        
}

DuplicateRemovePanel::~DuplicateRemovePanel()
{
    Disconnect(EVT_MALWARE_SCAN_STATUS, wxThreadEventHandler(DuplicateRemovePanel::OnGUIStatus));
    Disconnect(EVT_MALWARE_SCAN_ERROR, wxThreadEventHandler(DuplicateRemovePanel::OnGUIError));
    Disconnect(EVT_MALWARE_SCAN_NEWFILE, wxThreadEventHandler(DuplicateRemovePanel::OnGUINewFile));
    Disconnect(EVT_MALWARE_SCAN_FINISH, wxThreadEventHandler(DuplicateRemovePanel::OnGUIScanFinish));       
    Disconnect(EVT_MALWARE_DELETE_FILE, wxThreadEventHandler(DuplicateRemovePanel::OnGUIDeleteFile));
    Disconnect(EVT_MALWARE_DELETE_FINISH, wxThreadEventHandler(DuplicateRemovePanel::OnGUIDeleteFinish));
}

void DuplicateRemovePanel::CreateChildControls()
{
    CreatePanels();

    wxStaticText* locationText = new wxStaticText(scanPanel, wxID_ANY, "Location: ", wxPoint(20, 20));
    wxFont font = locationText->GetFont();
    //font.SetWeight(wxFONTWEIGHT_BOLD);    
    wxFont boldFont;
    boldFont.Create(font.GetPixelSize(), font.GetFamily(), wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    locationText->SetFont(boldFont);
    
    locationEdit = new wxTextCtrl(scanPanel, 1001, wxEmptyString, wxPoint(80, 20), wxSize(320, 16), wxBORDER_NONE);    
    startButton = new wxButton(scanPanel, 1002, "Start", wxPoint(80, 42));

    statusLabel = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(20, 100));
    statusLabel->SetFont(boldFont);
    statusLabel->Hide();

    errorLabel = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(20, 400));
    errorLabel->SetForegroundColour(wxColor(255, 0, 0));

    
    pathLabel = new wxStaticText(scanPanel, wxID_ANY, "Path: ", wxPoint(20, 130));
    pathLabel->SetFont(boldFont);
    pathLabel->Hide();
    pathText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(105, 130), wxSize(655, 15), wxST_ELLIPSIZE_MIDDLE);
       
    fileSizeLabel = new wxStaticText(scanPanel, wxID_ANY, "Size: ", wxPoint(20, 150));
    fileSizeLabel->SetFont(boldFont);
    fileSizeLabel->Hide();
    fileSizeText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(105, 150));
    fileSizeText->Hide();

    filesCountLabel = new wxStaticText(scanPanel, wxID_ANY, "Scanned Files: ", wxPoint(20, 200));
    filesCountLabel->SetFont(boldFont);
    filesCountText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(227, 200), wxSize(60, 16), wxALIGN_RIGHT);
    filesCountLabel->Hide();
    filesCountText->Hide();
    
    duplicatedCountLabel = new wxStaticText(scanPanel, wxID_ANY, "Duplicated Files: ", wxPoint(20, 220));
    duplicatedCountLabel->SetFont(boldFont);
    duplicatedCountText = new wxStaticText(scanPanel, wxID_ANY, "", wxPoint(227, 220), wxSize(60, 16), wxALIGN_RIGHT);
    duplicatedCountLabel->Hide();
    duplicatedCountText->Hide();

    cleanButton = new wxButton(scanPanel, 1003, "Clean...", wxPoint(300, 205));
    cleanButton->Hide();
    
    wxStaticText* checkListBoxLabel = new wxStaticText(deletePanel, wxID_ANY, "List of duplicated files:", wxPoint(20, 12));
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

    Bind(wxEVT_LISTBOX, &DuplicateRemovePanel::OnSelectedFileToDelete, this, 2001);

    Bind(wxEVT_BUTTON, &DuplicateRemovePanel::OnStartButton, this, 1002);
    Bind(wxEVT_BUTTON, &DuplicateRemovePanel::OnCleanButton, this, 1003);
    Bind(wxEVT_BUTTON, &DuplicateRemovePanel::OnReturnButton, this, 2002);
    Bind(wxEVT_BUTTON, &DuplicateRemovePanel::OnRemoveButton, this, 2003);
}

void DuplicateRemovePanel::paintEvent(wxPaintEvent & evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

void DuplicateRemovePanel::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

void DuplicateRemovePanel::render(wxDC&  dc)
{
}

void DuplicateRemovePanel::OnStatus(void* context, const wchar_t* status)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_STATUS);
    evt->SetString(status);
    wxQueueEvent(handler, evt);
}

void DuplicateRemovePanel::OnError(void* context, const wchar_t* errorText, int errorType)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_ERROR);
    evt->SetString(errorText);
    evt->SetInt(errorType);
    wxQueueEvent(handler, evt);
}

void DuplicateRemovePanel::OnScanFinish(void* context)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;
    ((DuplicateRemovePanel*)context)->inProgress = false;
    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_FINISH);
    wxQueueEvent(handler, evt);
}

void DuplicateRemovePanel::OnNewFile(void* context, const wchar_t* path, unsigned long long size, const wchar_t* hash, int notificationType)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_SCAN_NEWFILE);
    NewFileEventData* obj = new NewFileEventData();

    obj->current_path = path;
    obj->hash = hash;
    obj->notificationType = notificationType;
    obj->size = size;    

    evt->SetEventObject(obj);
    wxQueueEvent(handler, evt);
}

void DuplicateRemovePanel::OnGUIStatus(wxThreadEvent& event)
{
    wxString statusString = event.GetString();
    statusLabel->SetLabel(statusString);
    statusLabel->Show();
}

void DuplicateRemovePanel::OnGUIError(wxThreadEvent& event)
{
    wxString errorString = event.GetString();
    int errorType = event.GetInt();
    errorLabel->SetLabel(errorString);
    errorLabel->Show();
}

void DuplicateRemovePanel::OnStartButton(wxCommandEvent& event)
{
    if (!inProgress)
    {
        startButton->SetLabelText("Stop");
        locationEdit->Enable(false);
        
        inProgress = true;
        
        checkListBox->Clear();
        cleanButton->Hide();

        inProgress = true;
        std::list<wxString> locationList;
        locationList.push_back(locationEdit->GetValue());
        
        stopFlag = 0;
        fileCount = 0;
        duplicateCount = 0;
        
        DuplicateScanThread* scanThread = new DuplicateScanThread(this, locationList);
        scanThread->SetOnStatus(OnStatus, this);
        scanThread->SetOnError(OnError, this);
        scanThread->SetOnFinish(OnScanFinish, this);
        scanThread->SetOnNewFile(OnNewFile, this);
        /*
        scanThread->SetOnScheduled(OnScheduled, this);
        scanThread->SetOnMalicious(OnMalicious, this);
        */
        scanThread->SetIsStopped(IsProcessStopped, this);
        currentThread = scanThread;
        currentThread->Run();        
    }
    else
    {
        Stop();
    }
}

void DuplicateRemovePanel::OnCleanButton(wxCommandEvent& event)
{
    SwitchToDelete();
}

void DuplicateRemovePanel::OnReturnButton(wxCommandEvent& event)
{
    SwitchToScan();
}

void DuplicateRemovePanel::OnRemoveButton(wxCommandEvent& event)
{
    checkListBox->Enable(false);
    removeButton->Enable(false);
    returnButton->Enable(false);
    szSelectedDirText->SetLabelText("");
    szSelectedFileText->SetLabelText("");
    
    DuplicateDeleteThread* deleteThread = new DuplicateDeleteThread(this, checkListBox);
    deleteThread->SetOnDeleteFile(OnDeleteFile, this);
    deleteThread->SetOnFinish(OnDeleteFinish, this);
    deleteThread->SetIsStopped(IsProcessStopped, this);
    currentThread = deleteThread;
    currentThread->Run();
}

void DuplicateRemovePanel::OnSelectedFileToDelete(wxCommandEvent& event)
{
    int index = event.GetInt();
    wxOwnerDrawn* item = checkListBox->GetItem(index);
    wxString name = item->GetName();

    boost::filesystem::path Path = name;

    szSelectedDirText->SetLabelText(Path.parent_path().c_str());
    szSelectedFileText->SetLabelText(Path.filename().c_str());
}

void DuplicateRemovePanel::OnGUINewFile(wxThreadEvent& event)
{
    NewFileEventData* obj = (NewFileEventData*)event.GetEventObject();

    char countText[128];
    pathText->Show();
    pathLabel->Show();

    pathText->SetLabel(obj->current_path);

    if (obj->notificationType == 0)
    {
        //fileSizeLabel->SetLabel("Size:");        
        //sprintf(countText, "%I64u", obj->size);
        //fileSizeText->SetLabel(countText);
        fileCount++;
    }
    if (obj->notificationType == 1)
    {
        //fileSizeLabel->SetLabel("Hash:");        
        //fileSizeText->SetLabel(obj->hash);
    }
    if (obj->notificationType == 2)
    {
        //fileSizeLabel->Hide();
        //fileSizeText->Hide();

        duplicateCount++;
        sprintf(countText, "%d", duplicateCount);
        duplicatedCountText->SetLabel(countText);

        duplicatedCountLabel->Show();
        duplicatedCountText->Show();

        checkListBox->Append(obj->current_path);
    }
    
    sprintf(countText, "%d", fileCount);
    filesCountLabel->Show();
    filesCountText->Show();
    filesCountText->SetLabel(countText);
        
    //fileSizeLabel->Show();
    //fileSizeText->Show();
    
    delete obj;
}

void DuplicateRemovePanel::OnDeleteFile(void* context, int index)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;

    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_DELETE_FILE);
    evt->SetInt(index);
    wxQueueEvent(handler, evt);
}

void DuplicateRemovePanel::OnDeleteFinish(void* context)
{
    wxEvtHandler* handler = (wxEvtHandler*)context;
    ((DuplicateRemovePanel*)context)->inProgress = false;
    wxThreadEvent* evt = new wxThreadEvent(EVT_MALWARE_DELETE_FINISH);
    wxQueueEvent(handler, evt);
}

void DuplicateRemovePanel::OnGUIScanFinish(wxThreadEvent& event)
{
    startButton->SetLabelText("Start");

    pathText->Hide();
    pathLabel->Hide();
    statusLabel->Hide();
    fileSizeLabel->Hide();
    fileSizeText->Hide();
  

    inProgress = false;
    currentThread = NULL;

    if (duplicateCount > 0)
        cleanButton->Show();

    if (IsProcessStopped(this))
        wxMessageBox("Stopped");
    else
        wxMessageBox("Finished");
}

void DuplicateRemovePanel::OnGUIDeleteFile(wxThreadEvent& event)
{
    int deleteIndex = event.GetInt();
    checkListBox->Delete(deleteIndex);
}

void DuplicateRemovePanel::OnGUIDeleteFinish(wxThreadEvent& event)
{    
    checkListBox->Enable(true);
    removeButton->Enable(true);
    returnButton->Enable(true);

    if (checkListBox->GetCount() == 0)
        removeButton->Hide();
}