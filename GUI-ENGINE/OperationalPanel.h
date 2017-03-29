#pragma once

class OperationalPanel : public wxWindow
{
protected:
    wxThread* currentThread;
    wxPanel* scanPanel;
    wxPanel* deletePanel;

    wxCriticalSection cs;
    int stopFlag;
    bool inProgress;
    
    static bool IsProcessStopped(void* context);
    void Wait();
public:
    OperationalPanel(wxFrame* parent);
    ~OperationalPanel();

    void CreatePanels();

    void SwitchToScan();
    void SwitchToDelete();

    void Stop();
};
