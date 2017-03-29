// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include"scanner.h"
#include<string>
#include<list>
#include<map>


template<typename shortcuts>
class ShortCutVirusRemover:public Scanner
{
private:
	bool can_start = false;
	int count_of_shortcuts = 0;
	bool infection_sign = false;
	bool is_scan_complete = false;
	int suspected_file_id = 0; // Gets the unique ID for the suspected file
	// The drive letter
	std::string drive;
	//Shortucts ID
	int shortcuts_id = 0;
	std::map<int,shortcuts> shortcuts_location;
	std::map<int, shortcuts> suspected;
public:
	ShortCutVirusRemover();
	bool get_scan_status();
	void set_drive_letter(std::string drive_letter);
	bool scan(const wchar_t* sDir); // scanning for the shortcuts
	void remove_all_shotcuts(); // removes all .lnk files
	bool fix_infection(); // fixing all the attributes of the files and folders
	void show_suspected_files(); //This function is used to show the suspected files
};
