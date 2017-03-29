#include <wx\wxprec.h>
#include <wx\sizer.h>


#include "OperationalPanel.h"



OperationalPanel::OperationalPanel(wxFrame* parent)
    : wxWindow(parent, wxID_ANY)
{
    inProgress = false;
}

void OperationalPanel::Wait()
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

void OperationalPanel::CreatePanels()
{
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    verticalSizer->Add(horizontalSizer, 1, wxEXPAND);
    SetSizer(verticalSizer);

    scanPanel = new wxPanel(this);
    horizontalSizer->Add(scanPanel, 1, wxEXPAND);
    deletePanel = new wxPanel(this);
    horizontalSizer->Add(deletePanel, 1, wxEXPAND);

    scanPanel->SetBackgroundColour(wxColor(252, 250, 245));

    deletePanel->SetBackgroundColour(wxColor(248, 251, 252));
    deletePanel->Hide();
}

OperationalPanel::~OperationalPanel()
{
}

void OperationalPanel::SwitchToScan()
{
    deletePanel->Hide();
    scanPanel->Show();
    Layout();
}

void OperationalPanel::SwitchToDelete()
{
    scanPanel->Hide();
    deletePanel->Show();
    Layout();
}

void OperationalPanel::Stop()
{
    cs.Enter();
    stopFlag = 1;
    cs.Leave();
}

bool OperationalPanel::IsProcessStopped(void* context)
{
    if (context)
    {
        OperationalPanel* panel = (OperationalPanel*)context;
        panel->cs.Enter();
        bool stopped = (panel->stopFlag != 0);
        panel->cs.Leave();
        return stopped;
    }
    return false;
}