// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<wx\utils.h>
#include"utilities.h"

// Added Unicode support and tested!

/*
====================================================================================
Need a GUI developer to add this into the neat and clean Display
=====================================================================================
*/

template<typename T>
class Identity
{
private:
	//Os Information
	T os_info = wxGetOsDescription();
	//Os version
	T os_version = std::to_wstring(wxGetOsVersion());
	//Home Directory
	T home_dir = wxGetHomeDir();
	// User Name
	T user_name = wxGetUserName();
	// Is 64-bit OS
	bool is_64Bit = wxIsPlatform64Bit();
	// Host name
	T host = wxGetHostName();
	// Getting Ram Size in Giga Bytes
	wxString ramSize = getSizeofRam();
public:
	void display();
};
