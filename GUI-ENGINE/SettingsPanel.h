#pragma once

class SettingsPanel : public wxWindow
{
public:    
    SettingsPanel(wxFrame* parent);
    ~SettingsPanel();

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    DECLARE_EVENT_TABLE()
};

