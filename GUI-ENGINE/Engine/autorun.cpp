// SWAMI KARUPPASWAMI THUNNAI

#include"autorun.h"
#include"conversions.h"
#include"utilities.h"
#include"extensions.h"
#include<fstream>
#include<exception>
#include<regex>
#include<locale>
#include<codecvt>
#include<boost\filesystem.hpp>
#include<boost\algorithm\string.hpp>
#include<wx\msgdlg.h>

template<typename autoruns>
bool Autorun<autoruns>::scan(const wchar_t * sDir)
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
				try {
					std::wstring path = wide_char_to_wide_string(current_path);
					// Used to get the extension
					boost::filesystem::path PATH = path;
					std::string extension = PATH.extension().string();
					// Iterator to find whether extensions are in the list
					std::set<std::string>::iterator find_exten_match = valid_extensions_list.find(extension);
					if (find_exten_match != valid_extensions_list.end()) 
					{
						//used to get the size
						long double Size = boost::filesystem::file_size(path);
						// Iterator to find whether the size matches in the list
						std::set<long double>::iterator find_size_match = size_list.find(Size);
						std::cout << "Scanning : " << path << "\n";
						if (find_size_match != size_list.end())
						{
							//used to get the md5
							std::string Hash = calculate_md5(path);
							// Iterator to find whether the hash matches in the list
							std::set<std::string>::iterator find_hash_match = hash_list.find(Hash);
							if (find_hash_match != hash_list.end())
							{
								std::cout << "Found the path :" << path << "\n";
								autorun_file_list[located_autorun_id] = path;
								located_autorun_id++;
							}
						}
					}
					else std::cout << "[SKIPPING]: " << path << "\n";
				}
				catch (std::exception &e)
				{
					std::cout << e.what();
					//use logging for safety
					std::ofstream file;
					file.open("logs\\autoruns.log", std::ios::app);
					if (file.is_open())
					{
						file << e.what();
						file.close();
					}
				}

			}
		}
	} while (FindNextFile(hFind, &find_file));

	FindClose(hFind);

	return true;
}


// autorun_file is the location of autorun.inf
// autorun_files is a std::map which consists of the list of suspicious files
template<typename autoruns>
bool Autorun<autoruns>::add_autorun_executables(std::string drive)
{
	std::string autorun_file = drive + "autorun.inf";
	if (!std::ifstream(autorun_file))
	{
		//MessageBeep(700);
		//wxMessageBox("No autorun file is found", "CyberGod KSGMPRH");
		return false;
	}
	else
	{
		std::ifstream file(autorun_file);
		if (file.is_open())
		{
			std::string detect_file;
			while (!file.eof())
			{
				file >> detect_file;
				// Use this pattern to detect the file
				// which gets executed on autorun
				std::regex pattern("open.*");
				bool match = std::regex_match(detect_file, pattern);
				if (match)
				{
					boost::trim(detect_file);
					detect_file.erase(0, 5);
					//we are getting the executables which will be
					//executed on auto-run for suspicious checking
					std::cout << "Autorun File: " << detect_file;
					std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert_this;
					std::wstring complete_file = convert_this.from_bytes(drive+detect_file);
					autorun_files[autorun_id] = complete_file; //specify the id along with the file
					//getting the extension of the file to be checked
					boost::filesystem::path PATH = drive + detect_file;
					std::string extension = PATH.extension().string();
					std::cout << "The extension of the file present in the autorun.inf is " << extension << "\n";
					try
					{
						valid_extensions_list.insert(extension);
					}
					catch (std::exception &e)
					{
						std::cout << e.what();
					}
					autorun_id++; //increment the id with one
				}
			}
			file.close(); //close the file
						  // Inform the user about the files which gets executed on autorun
						  // Need a GUI DEV to neatly present this
			std::map<int, autoruns>::iterator itr1 = autorun_files.begin();
			std::map<int, autoruns>::iterator itr2 = autorun_files.end();
			std::cout << "\nID\t\tNAME\n";
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			for (std::map<int, autoruns>::iterator itr = itr1; itr != itr2; ++itr)
			{
				std::cout << itr->first << "\t\t" << itr->second << "\n";
			}
		}
		else
		{
			std::cout << "File is already opened somewhere\n";
		}
		return true;
	}
}

template<typename autoruns>
bool Autorun<autoruns>::check_autorun_file()
{
	if(autorun_files.empty())	return false;
	else return true;
}


// This function is used to compute the hashes for all the files present in autorun.inf

template<typename autoruns>
void Autorun<autoruns>::get_hashes()
{
	typedef std::map<int, autoruns>::iterator iterator;
	iterator itr1 = autorun_files.begin();
	iterator itr2 = autorun_files.end();
	for (iterator itr = itr1; itr != itr2; ++itr)
	{
		std::cout << itr->second;
		if (std::ifstream(itr->second))
		{
			long double size = boost::filesystem::file_size(itr->second);
			std::string hash = calculate_md5(itr->second);
			try
			{
				std::cout << "Size " << size << "\n";
				size_list.insert(size);
			}
			catch (std::exception &e)
			{
				std::cout << e.what();
			}
			try
			{
				std::cout << "Hash " << hash << "\n";
				hash_list.insert(hash);
			}
			catch (std::exception &e)
			{
				std::cout << e.what();
			}
			
		}
	}
	std::cout << "Computed all the file sizes and hashes successfully";
}

template<typename autoruns>
bool Autorun<autoruns>::check_this_file(std::string hash)
{
	typedef std::set<std::string>::iterator iterator;
	iterator itr1 = hash_list.find(hash);
	if (itr1 != hash_list.end())return true;
	return false;
}

template<typename autoruns>
void Autorun<autoruns>::locate()
{
	for (int i = 0; i < no_of_volumes; i++)
	{
		// Will get the current drive letter
		std::string current_scanning_drive = volume[i];
		std::cout << "Scanning the drive : " << current_scanning_drive << "\n";
		scan(string_wide_pointer(current_scanning_drive));	
	}
}

template<typename autoruns>
void Autorun<autoruns>::display()
{
	system("cls");
	typedef std::map<int, autoruns>::iterator iterator;
	iterator itr1 = autorun_file_list.begin();
	iterator itr2 = autorun_file_list.end();
	std::cout << "Malicious Detections\n=================================\n";
	for (iterator itr = itr1; itr != itr2; ++itr)
	{
		std::cout << itr->first << "\t" << itr->second << "\n";
	}
}

template class Autorun<std::wstring>;