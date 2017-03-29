#include <wx/wxprec.h>
#include <wx/gdicmn.h>

#include "Logo.h"

wxStaticBitmap *image;

BEGIN_EVENT_TABLE(Logo, wxPanel)
// catch paint events
EVT_PAINT(Logo::paintEvent)

END_EVENT_TABLE()

Logo::Logo(wxFrame* parent) :
    wxWindow(parent, wxID_ANY)
{
    SetMinSize(wxSize(129, 80));

    wxPNGHandler *handler = new wxPNGHandler;
    wxImage::AddHandler(handler);

    bitmap = new wxBitmap("CG-Black.png", wxBITMAP_TYPE_PNG);
}

Logo::~Logo()
{
    delete bitmap;
}

void Logo::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);

    wxSize dstSize = GetSize();
    wxSize srcSize = bitmap->GetSize();
    wxPoint topLeft(0, 0);

    wxImage image = bitmap->ConvertToImage();
    wxBitmap scaled = image.Scale(dstSize.GetWidth(), dstSize.GetHeight(), wxIMAGE_QUALITY_HIGH);
    
    dc.DrawBitmap(scaled, topLeft);

    /*
    wxMemoryDC mdc;
    mdc.SelectObject(*bitmap);                       
    dc.StretchBlit(topLeft, dstSize, &mdc, topLeft, srcSize, wxCOPY);
    */
}