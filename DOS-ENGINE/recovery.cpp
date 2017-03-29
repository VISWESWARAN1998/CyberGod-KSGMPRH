// SWAMI KARUPPASWAMI THUNNAI
#include <Windows.h>
#include<exception>
#include"extensions.h"
#include"conversions.h"
#include "recovery.h"
#include<boost\filesystem.hpp>
#include<wx/msgdlg.h>



//Parameterized constructor to set up the recycle bin path
template<typename recovers>
Recovery<recovers>::Recovery(recovers drive_letter,recovers recovery_location)
{
	//locating the recycle bin...
	recovers complete_string = drive_letter + "$RECYCLE.BIN";
	//Make it as a wide character...
	std::wstring Path(complete_string.begin(),complete_string.end());
	// we are setting up the path
	recycle_bin = Path.c_str();
	std::wcout << "\n\n" << recycle_bin;
	recovery_directory_location = recovery_location;
	//This will be our default recovery folder
	std::string title = "CyberGod Recovery Data";
	//create our directory here
	boost::filesystem::path directory(recovery_location + title);
	recovery_directory_location = recovery_location + title;
	if (boost::filesystem::create_directory(directory))
	{
		//Need a GUI Developer to add this to GUI
		std::cout << "Directory has been created";
	}
	else
	{
		//Need a GUI dev to handle this in GUI
		wxMessageBox("Unable to create the directory on the specified location", "CyberGod KSGMPRH -error");
	}
	scan(recycle_bin);
	const wchar_t* drive_letter_for_dollar_scan = drive_letter.c_str();
	non_user_file_scan(drive_letter_for_dollar_scan);
}


// the scanner which has been implemented for the recovering of the files function
template<typename recovers>
bool Recovery<recovers>::scan(const wchar_t * sDir)
{
	WIN32_FIND_DATA find_file;
	HANDLE hFind = NULL;
	wchar_t current_path[2048];
	wsprintf(current_path, L"%s\\*.*", sDir);

	if ((hFind = FindFirstFile(current_path, &find_file)) == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Path not found: [%s]\n", sDir);
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
			else
			{
				//This consists of current path
				recovers Path = wide_char_to_wide_string(current_path);
				boost::filesystem::path p = { Path };
				// we got the extension of the file
				std::string extension = p.extension().string();
				// we need file name too
				recovers name_of_file = p.filename().wstring();
				bool can_scan = is_safe_recoverable_format(extension);
				//and also the file size
				long double size = file_size(p);
				// If the file can be scanned
				if (can_scan == true)
				{
					std::cout << "Trying to recover "<<name_of_file<<"\n";
					boost::filesystem::path source(Path);
					boost::filesystem::path destination(recovery_directory_location+"//"+name_of_file);
					try {
						boost::filesystem::copy_file(source, destination);
					}
					catch (std::exception &e)
					{
						std::cout << "\nException thrown out :" << e.what() << "\n";
					}
					std::cout << "Recovered " << name_of_file << "\n";
				}
			}
		}
	} while (FindNextFile(hFind, &find_file));
	FindClose(hFind);
	return true;
	return true;
}


// DEFINITION: the $ recovery snippet of the code
template<typename recovers>
bool Recovery<recovers>::non_user_file_scan(const wchar_t * sDir)
{
	WIN32_FIND_DATA find_file;
	HANDLE hFind = NULL;
	wchar_t current_path[2048];
	Extensions check_extensions;
	wsprintf(current_path, L"%s\\*.*", sDir);

	if ((hFind = FindFirstFile(current_path, &find_file)) == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Path not found: [%s]\n", sDir);
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
			else 
			{
				//This consists of current path
				recovers Path = wide_char_to_wide_string(current_path);
				boost::filesystem::path p = { Path };
				// we got the extension of the file
				std::string extension = p.extension().string();
				// we need file name too
				recovers name_of_file = p.filename().wstring();
				bool can_scan = is_safe_recoverable_format(extension);
				//and also the file size
				long double size = file_size(p);
				// If the file can be scanned
				if (can_scan == true)
				{
					if (name_of_file.at(0) == '$')
					{
						std::cout << "Trying to recover " << name_of_file << "\n";
						boost::filesystem::path source(Path);
						boost::filesystem::path destination(recovery_directory_location + "//" + name_of_file);
						try {
							boost::filesystem::copy_file(source, destination);
							std::cout << "Recovered " << name_of_file << "\n";
						}
						catch (std::exception &e)
						{
							std::cout << "\nException thrown out :" << e.what() << "\n";
						}
					}
				}
			}
		}
	} while (FindNextFile(hFind, &find_file));

	FindClose(hFind);
	return true;
}

template<typename recovers>
bool Recovery<recovers>::is_safe_recoverable_format(std::string extension)
{
	Extensions check_extensions;
	if (check_extensions.is_document(extension) == true)return true;
	else if (check_extensions.is_image(extension) == true)return true;
	else if (check_extensions.is_document(extension) == true)return true;
	else return false;
	return false;
}


template class Recovery<std::wstring>;