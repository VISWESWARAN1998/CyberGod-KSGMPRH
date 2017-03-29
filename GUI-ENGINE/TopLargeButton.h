#pragma once

class TopLargeButton : public wxWindow
{
    bool pressedDown;

    static const int buttonWidth = 80;
    static const int buttonHeight = 80;

    int command;
    wxBitmap* normalBitmap;
    wxBitmap* pressedBitmap;
public:
    TopLargeButton(wxFrame* parent, wxString text, int command);
    TopLargeButton(wxFrame* parent, wxString text, int command, wxString normalState, wxString pressedState);
    ~TopLargeButton();

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    // some useful events
    void mouseMoved(wxMouseEvent& event);
    void mouseDown(wxMouseEvent& event);
    void mouseWheelMoved(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void rightClick(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);
    void keyPressed(wxKeyEvent& event);
    void keyReleased(wxKeyEvent& event);

    DECLARE_EVENT_TABLE()

};
