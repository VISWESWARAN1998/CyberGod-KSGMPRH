// SWAMI KARUPPASWAMI THUNNAI
#include<Windows.h>
#include<Python.h>
#include<exception>
#include<fstream>
#include<regex>
#include "shortcutvirus.h"
#include"conversions.h"
#include"extensions.h"
#include"utilities.h"
#include<boost\filesystem.hpp>
#include<boost\algorithm\string.hpp>
#include<wx\msgdlg.h>


// First of all set the drive letter which is crucial for removing the shortcut virus
template<typename shortcuts>
void ShortCutVirusRemover<shortcuts>::set_drive_letter(std::string drive_letter)
{
	try
	{
		int status = get_drive_status(drive_letter);
		if (status != 2)throw - 1;
		else
		{
			drive = drive_letter;
			can_start = true;
		}
	}
	catch (int execp_no)
	{
		wxMessageBox("The dive is not a removable drive", "CyberGod KSGMPRH");
		can_start = false;
	}
}

// can we scan the drive - this is used to get the status nothing more
template<typename shortcuts>
bool ShortCutVirusRemover<shortcuts>::get_scan_status()
{
	return can_start;
}

// The scanner for scanning the shortcut virus infection
template<typename shortcuts>
bool ShortCutVirusRemover<shortcuts>::scan(const wchar_t * sDir)
{
	WIN32_FIND_DATA find_file;
	HANDLE hFind = NULL;
	wchar_t current_path[2048];
	Extensions check_extensions;
	wsprintf(current_path, L"%s\\*.*", sDir);

	if ((hFind = FindFirstFile(current_path, &find_file)) == INVALID_HANDLE_VALUE)
	{
		//Add a message box for invalid path - GUI Dev needed
		return false;
	}

	do
	{
		if (wcscmp(find_file.cFileName, L".") != 0
			&& wcscmp(find_file.cFileName, L"..") != 0)
		{
			wsprintf(current_path, L"%s\\%s", sDir, find_file.cFileName);
			if (find_file.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			{
				scan(current_path);
			}
			else {
				shortcuts file_location = wide_char_to_wide_string(current_path);

				//If it is a shortcut
				//List of shortcuts we need to append it into the list box lively
				//It is important
				boost::filesystem::path p = { file_location };
				// we got the extension of the file
				std::string extension = p.extension().string();
				if (check_extensions.is_shortcut(extension) == true)
				{
					infection_sign = true; //set the infection sign true
					std::cout << "Shortcut Found";
					count_of_shortcuts++; // increment the count the shortcuts
					std::cout << "\nCount: " << count_of_shortcuts;
					shortcuts_location[shortcuts_id] = file_location;
					//Increment the ID of the shortcuts
					shortcuts_id++;
				}
				// The suspected files are pushed back
				if (check_extensions.is_common_extension(extension) == true)
				{
					// It is a map so that we can actually remove using the 
					// unique suspected file ID
					suspected[suspected_file_id] = file_location;
					suspected_file_id++;//increment it for sure
				}
			}
		}
	} while (FindNextFile(hFind, &find_file));

	FindClose(hFind);
	is_scan_complete = true;
	return true;
}

// checks and removes all .lnk files in the desired drive
template<typename shortcuts>
void ShortCutVirusRemover<shortcuts>::remove_all_shotcuts()
{
	// Remove all the shorcuts
	if (is_scan_complete == true)
	{
		if (shortcuts_location.empty())
		{
			MessageBeep(700);
			MessageBox(NULL, L"No shortcuts found on the drive", L"CyberGod KSGMPRH", MB_OK);
		}
		else
		{
			std::map<int,shortcuts>::iterator itr1 = shortcuts_location.begin();
			std::map<int,shortcuts>::iterator itr2 = shortcuts_location.end();
			for (std::map<int,shortcuts>::iterator itr = itr1; itr != itr2; itr++)
			{
				utilityRemove(itr->second);
			}
		}
	}
}


// using command prompt to fix the infection
template<typename shortcuts>
bool ShortCutVirusRemover<shortcuts>::fix_infection()
{
	std::string command = "attrib -h -r -s /s /d "+drive+"*.*";
	// Remove all those properties of hidden files
	system(command.c_str());
	wxMessageBox("CyberGod KSGMPRH", "Successfully restored all your hidden files and folders");
	return true;
}

// This is used to show what are the files are suspected to be malware
// Need a GUI developer to add this stuff to the checked list box so that a user can select
// and remove

template<typename shortcuts>
void ShortCutVirusRemover<shortcuts>::show_suspected_files()
{
	
	std::map<int, shortcuts>::iterator itr1 = suspected.begin();
	std::map<int, shortcuts>::iterator itr2 = suspected.end();
	for (std::map<int, shortcuts>::iterator itr = itr1; itr != itr2; itr++)
	{
		std::cout << "SUSPECTED: " << itr->first << "\t" << itr->second << "\n";
	}
}


template class ShortCutVirusRemover<std::wstring>;
