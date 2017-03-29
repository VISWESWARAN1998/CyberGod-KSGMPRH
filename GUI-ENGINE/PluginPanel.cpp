#include <list>
#include <fstream>
#include <boost\algorithm\string\trim.hpp>
#include <wx/wxprec.h>
#include <wx/sizer.h>

#include "PluginPanel.h"

BEGIN_EVENT_TABLE(PluginPanel, wxPanel)
// catch paint events
// EVT_PAINT(PluginPanel::paintEvent)
END_EVENT_TABLE()

PluginPanel::PluginPanel(wxFrame* parent) : wxWindow(parent, wxID_ANY)
{
}

PluginPanel::~PluginPanel()
{
}

void PluginPanel::CreateChildControls()
{    
    wxStaticText* listBoxLabel = new wxStaticText(this, wxID_ANY, "List of plugins:", wxPoint(20, 12));
    // checkListBoxLabel->SetFont(boldFont);
    pluginListBox = new wxListBox(this, 2001, wxPoint(20, 30), wxSize(730, 310));
    long style = wxBORDER_NONE | pluginListBox->GetWindowStyle();
    pluginListBox->SetWindowStyle(style);
}

void PluginPanel::paintEvent(wxPaintEvent & evt)
{

}

void PluginPanel::paintNow()
{

}

void PluginPanel::render(wxDC& dc)
{

}

void PluginPanel::FillPluginList()
{
    pluginListBox->Clear();
    
}

void PluginPanel::get_available_plugins()
{
    if (std::ifstream("cybergod.plugins"))
    {
        std::ifstream file;
        file.open("cybergod.plugins");
        while (!file.eof())
        {
            std::string locations;
            std::getline(file, locations);
            if (locations != "")
            {
                boost::algorithm::trim_right(locations);
                boost::algorithm::trim_left(locations);
                //std::cout << locations;
                //available_plugins.push_back(locations);
            }
        }
    }
    else
    {
        MessageBeep(700);
        MessageBox(NULL, L"Create cybergod.plugins file and start adding your plugins", L"CyberGod KSGMPRH - locations not found", MB_OK);
    }

}

