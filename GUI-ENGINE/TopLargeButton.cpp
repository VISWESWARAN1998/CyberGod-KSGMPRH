#include <wx/wxprec.h>
#include <wx/sizer.h>

#include "TopLargeButton.h"
#include "MainFrame.h"
#include "Commands.h"

BEGIN_EVENT_TABLE(TopLargeButton, wxPanel)

EVT_MOTION(TopLargeButton::mouseMoved)
EVT_LEFT_DOWN(TopLargeButton::mouseDown)
EVT_LEFT_UP(TopLargeButton::mouseReleased)
EVT_RIGHT_DOWN(TopLargeButton::rightClick)
EVT_LEAVE_WINDOW(TopLargeButton::mouseLeftWindow)
EVT_KEY_DOWN(TopLargeButton::keyPressed)
EVT_KEY_UP(TopLargeButton::keyReleased)
EVT_MOUSEWHEEL(TopLargeButton::mouseWheelMoved)

// catch paint events
EVT_PAINT(TopLargeButton::paintEvent)

END_EVENT_TABLE()


TopLargeButton::TopLargeButton(wxFrame* parent, wxString text, int command) :
    wxWindow(parent, wxID_ANY)
{
    SetMinSize(wxSize(buttonWidth, buttonHeight));
    this->command = command;
    pressedDown = false;    

	normalBitmap = NULL;
    pressedBitmap = NULL;
}

// Constructor for adding buttons with bitmap
TopLargeButton::TopLargeButton(wxFrame* parent, wxString text, int command, wxString normalState, wxString pressedState) :
    wxWindow(parent, wxID_ANY)
{
    SetMinSize(wxSize(buttonWidth, buttonHeight));
    this->command = command;
    pressedDown = false;

    normalBitmap = new wxBitmap(normalState, wxBITMAP_TYPE_PNG);
    pressedBitmap = new wxBitmap(pressedState, wxBITMAP_TYPE_PNG);

    long style = wxBORDER_NONE | GetWindowStyle();
    SetWindowStyle(style);
}

TopLargeButton::~TopLargeButton()
{
    if (normalBitmap)
        delete normalBitmap;

    if (pressedBitmap)
        delete pressedBitmap;
}

/*
* Called by the system of by wxWidgets when the panel needs
* to be redrawn. You can also trigger this call by
* calling Refresh()/Update().
*/

void TopLargeButton::paintEvent(wxPaintEvent & evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

/*
* Alternatively, you can use a clientDC to paint on the panel
* at any time. Using this generally does not free you from
* catching paint events, since it is possible that e.g. the window
* manager throws away your drawing when the window comes to the
* background, and expects you will redraw it when the window comes
* back (by sending a paint event).
*/
void TopLargeButton::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

/*
* Here we do the actual rendering. I put it in a separate
* method so that it can work no matter what type of DC
* (e.g. wxPaintDC or wxClientDC) is used.
*/
void TopLargeButton::render(wxDC&  dc)
{
    if (pressedDown)
    {        
        if (!pressedBitmap)
        {
            dc.SetBrush(*wxRED_BRUSH);
            dc.DrawRectangle(0, 0, buttonWidth, buttonHeight);
        }
        else
        {
            wxSize dstSize = GetSize();
            wxSize srcSize = pressedBitmap->GetSize();
            wxPoint topLeft(0, 0);

            wxImage image = pressedBitmap->ConvertToImage();
            wxBitmap scaled = image.Scale(dstSize.GetWidth(), dstSize.GetHeight(), wxIMAGE_QUALITY_HIGH);

            dc.DrawBitmap(scaled, topLeft);
        }
    }
    else
    {
        if (!normalBitmap)
        {
            dc.SetBrush(*wxGREY_BRUSH);
            dc.DrawRectangle(0, 0, buttonWidth, buttonHeight);
        }
        else
        {
            wxSize dstSize = GetSize();
            wxSize srcSize = normalBitmap->GetSize();
            wxPoint topLeft(0, 0);

            wxImage image = normalBitmap->ConvertToImage();
            wxBitmap scaled = image.Scale(dstSize.GetWidth(), dstSize.GetHeight(), wxIMAGE_QUALITY_HIGH);

            dc.DrawBitmap(scaled, topLeft);
        }
    }

    //
    //dc.DrawText(text, 20, 15);
}

void TopLargeButton::mouseDown(wxMouseEvent& event)
{
    pressedDown = true;
    paintNow();
}
void TopLargeButton::mouseReleased(wxMouseEvent& event)
{
    if (pressedDown)
    {
        MainFrame* mainFrame = (MainFrame*)GetParent();
        switch(command)
        {
            case ID_SCAN:        
                mainFrame->OnMalwareScan();
                break;
            case ID_DUPLICATE_REMOVE:
                mainFrame->OnDuplicateFiles();
                break;
            case ID_USB_SCAN:
                mainFrame->OnUSBScan();
                break;
            case ID_QUICK_SCAN:
                mainFrame->OnQuickScan();
                break;
            case ID_RECOVERY:
                mainFrame->OnRecovery();
                break;
            case ID_PLUGIN:
                mainFrame->OnPlugin();
                break;
            case ID_SETTINS:                
                mainFrame->OnSettings();
                break;              
        }
    }
    pressedDown = false;
    paintNow();

    //wxMessageBox(wxT("You pressed a custom button"));
}
void TopLargeButton::mouseLeftWindow(wxMouseEvent& event)
{
    if (pressedDown)
    {
        pressedDown = false;
        paintNow();
    }
}

// currently unused events
void TopLargeButton::mouseMoved(wxMouseEvent& event) {}
void TopLargeButton::mouseWheelMoved(wxMouseEvent& event) {}
void TopLargeButton::rightClick(wxMouseEvent& event) {}
void TopLargeButton::keyPressed(wxKeyEvent& event) {}
void TopLargeButton::keyReleased(wxKeyEvent& event) {}