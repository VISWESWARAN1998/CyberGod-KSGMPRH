// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<Windows.h>
#include<iostream>
#include<string>
#include<ctime>
#include<wx\volume.h>


class Scanner
{
protected:
	wxArrayString volume = wxFSVolume::GetVolumes();
	int no_of_volumes = volume.size();
public:
	Scanner(){}
	// General Purpose Scanner
	virtual bool scan(const wchar_t* sDir);
	std::string get_time();
	bool replace_file(std::wstring file_location);
	void secure_pass(std::wstring file_location,int pass=2);
};