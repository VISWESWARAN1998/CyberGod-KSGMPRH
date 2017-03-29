#include <wx/wxprec.h>
#include <wx/gdicmn.h>

#include "MainFrame.h"

class CyberGodApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(CyberGodApp);

bool CyberGodApp::OnInit()
{
	wxPNGHandler *handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
    MainFrame *frame = new MainFrame();
    frame->Show(true);
    return true;
}