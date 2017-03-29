#pragma once
// Currently we have no plugin system!
class PluginPanel : public wxWindow
{
    wxListBox *pluginListBox;
    void get_available_plugins();
public:
    PluginPanel(wxFrame* parent);
    ~PluginPanel();

    void CreateChildControls();
    void FillPluginList();

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    DECLARE_EVENT_TABLE()
};

