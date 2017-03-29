#include <wx/wxprec.h>
#include <wx/sizer.h>

#include "SettingsPanel.h"

BEGIN_EVENT_TABLE(SettingsPanel, wxPanel)
// catch paint events
// EVT_PAINT(SettingsPanel::paintEvent)
END_EVENT_TABLE()

SettingsPanel::SettingsPanel(wxFrame* parent) : wxWindow(parent, wxID_ANY)
{
}

SettingsPanel::~SettingsPanel()
{
}

void SettingsPanel::paintEvent(wxPaintEvent & evt)
{

}

void SettingsPanel::paintNow()
{

}

void SettingsPanel::render(wxDC& dc)
{

}
