#include <wx\wxprec.h>
#include "ThreadEvents.h"

// this must be in a .CPP file so that it only exists once in the project
wxDEFINE_EVENT(EVT_MALWARE_SCAN_STATUS, wxThreadEvent);
wxDEFINE_EVENT(EVT_MALWARE_SCAN_ERROR, wxThreadEvent);
wxDEFINE_EVENT(EVT_MALWARE_SCAN_FINISH, wxThreadEvent);
wxDEFINE_EVENT(EVT_MALWARE_SCAN_NEWFILE, wxThreadEvent);
wxDEFINE_EVENT(EVT_MALWARE_SCHEDULED, wxThreadEvent);
wxDEFINE_EVENT(EVT_MALWARE_SCAN_FOUND, wxThreadEvent);
wxDEFINE_EVENT(EVT_MALWARE_DELETE_FILE, wxThreadEvent);
wxDEFINE_EVENT(EVT_MALWARE_DELETE_FINISH, wxThreadEvent);
wxDEFINE_EVENT(EVT_RECOVERY_FILE, wxThreadEvent);