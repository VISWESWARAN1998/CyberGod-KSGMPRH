#pragma once

class Logo : public wxWindow
{
    wxBitmap* bitmap;
public:
    Logo(wxFrame* parent);
    ~Logo();
    void paintEvent(wxPaintEvent & evt);

    DECLARE_EVENT_TABLE()
};
