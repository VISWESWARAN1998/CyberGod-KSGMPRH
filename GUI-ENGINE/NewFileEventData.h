#pragma once

class NewFileEventData : public wxObject
{
public:
    wxString current_path;
    wxString extension;
    wxString hash;

    unsigned long long size;
    int notificationType;
};
