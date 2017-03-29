// SWAMI KARUPPASWAMI THUNNAI

#include<Windows.h>
#include"usb.h"
#include"utilities.h"
#include"conversions.h"
#include"malware_symptoms.h"
#include"extensions.h"
#include"sqlite_modern_cpp.h"
#include<boost\filesystem.hpp>

using namespace sqlite;

// This method will return true if the drive is a removable drive
template<typename usb>
inline bool USBScan<usb>::initialize(std::string drive)
{
	if (get_drive_status(drive) == 2)
	{
		drive_letter = drive;
		autoruns.add_autorun_executables(drive);
		if (autoruns.check_autorun_file() == true)autoruns.get_hashes();
		scan(string_wide_pointer(drive));
		return true;
	}
	return false;
}


/*
Rules for the scanner:

Rule 1:
Follow the malware scanner

Rule 2:
Follow the autorun.inf file

Rule 3:
Find the presence of shortcuts


*/

template<typename usb>
bool USBScan<usb>::scan(const wchar_t * sDir)
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
				usb path = wide_char_to_wide_string(current_path);
				boost::filesystem::path Path = path;
				std::string extension = Path.extension().string();
				// Rule 1:
				std::string hash = calculate_md5(path);
				if (check_in_database(hash) == true)
				{
					malicious_files[path] = "IDENTIFIED THREAT";
				}
				else if (is_upx(path) == true)semi_malicious_files[path] = "SUSPICIOUS PACKED";
				else if (autoruns.check_this_file(hash) == true)
				{
					try
					{
						files_scaned_for_pc[path] = hash;
					}
					catch (std::exception &e)
					{
						std::cout << e.what();
					}
				}
				else if (extension == ".exe")
				{
					try
					{
						files_scaned_for_pc[path] = hash;
						Beep(900, 50);
					}
					catch (std::exception &e)
					{
						std::cout << e.what();
					}
				}
				else std::cout << "\nSkipping..." <<path<< "\n";
			}
		}
	} while (FindNextFile(hFind, &find_file));

	FindClose(hFind);

	return true;
}

template<typename usb>
bool USBScan<usb>::check_in_database(std::string hash)
{
	bool status = false;
	try
	{
		// this is the location of the database, I think I need to change the location in
		//future
		database db("ksgmprh.db");
		std::string table_name(1, hash[0]);
		// the below one is used if the hash starts with any numericals then finding in appropirate tables 
		std::map<std::string, std::string> numericals;
		numericals["0"] = "zero";
		numericals["1"] = "one";
		numericals["2"] = "two";
		numericals["3"] = "three";
		numericals["4"] = "four";
		numericals["5"] = "five";
		numericals["6"] = "six";
		numericals["7"] = "seven";
		numericals["8"] = "eight";
		numericals["9"] = "nine";
		std::map<std::string, std::string>::iterator itr = numericals.find(table_name);
		// If the table name starts with numericals then,
		std::string query = "select hash,variant from ";
		if (itr != numericals.end())query += itr->second;
		else query += table_name;
		query += " where hash = ? ;";
		// so now we got our query properly
		db << query << hash >> [&](std::unique_ptr<std::string> value, std::string type) {
			if (value != nullptr) status = true;
			else status = false;
		};
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
		status = false;
	}
	return status;
}

// Used to show the identified threats
template<typename usb>
void USBScan<usb>::show_malicious_files()
{
	typedef std::map<usb, std::string>::iterator iterator;
	iterator itr1 = malicious_files.begin();
	iterator itr2 = malicious_files.end();
	for (iterator itr = itr1; itr != itr2; ++itr)
	{
		std::cout << itr->first << "\n";
	}
}

// used to show the semi malicious files
template<typename usb>
void USBScan<usb>::show_semi_malicious_files()
{
	typedef std::map<usb, std::string>::iterator iterator;
	iterator itr1 = semi_malicious_files.begin();
	iterator itr2 = semi_malicious_files.end();
	for (iterator itr = itr1; itr != itr2; ++itr)
	{
		std::cout << itr->first<<"\n";
	}
}

template<typename usb>
void USBScan<usb>::show_files_scanned_in_pc()
{
	typedef std::map<usb,std::string>::iterator iterator;
	iterator itr1 = files_scaned_for_pc.begin();
	iterator itr2 = files_scaned_for_pc.end();
	for (iterator itr = itr1; itr != itr2; ++itr)
	{
		std::cout << itr->first << "\n";
	}
}


template class USBScan<std::wstring>;