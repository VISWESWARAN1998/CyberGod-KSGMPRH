// SWAMI KKARUPPASWAMI THUNNAI

#include"scanner.h"
#include<fstream>
#include<vector>
#include<codecvt>
#include<exception>
#include"sha512.h"
#include<boost\filesystem.hpp>
#include "gutmann.h"
#include"conversions.h"
#include"utilities.h"
#include<wx\msgdlg.h>

std::string random_binary();
//This will be our method to remove a file it can't be recovered at any means
bool Scanner::replace_file(std::wstring file_location)
{
	try
	{
		//Invalid file location is most unlikely but may be helpful
		if (!boost::filesystem::exists(file_location))
		{
			wxMessageBox("File", "Not present");
			return false;
		}
		std::ofstream replace_file(file_location);
		int count = 1; // count of value
		int iterate_count = rand() % 1000 + 1;
		for (int i = 0; i < iterate_count;i++)
		{
			//Only 35 passess for processing gtumann's algorithm
			if (count == 36)count = 1;
			switch (count)
			{
			case 1:
				replace_file << random_binary();
				break;
			case 2:
				replace_file << random_binary();
				break;
			case 3:
				replace_file << random_binary();
				break;
			case 4:
				replace_file << random_binary();
				break;
			case 5:
				replace_file << "01010101 01010101 01010101";
				break;
			case 6:
				replace_file << "10101010 10101010 10101010";
				break;
			case 7:
				replace_file << "10010010 01001001 00100100";
				break;
			case 8:
				replace_file << "01001001 00100100 10010010";
				break;
			case 9:
				replace_file << "00100100 10010010 01001001";
				break;
			case 10:
				replace_file << "00000000 00000000 00000000";
				break;
			case 11:
				replace_file << "00010001 00010001 00010001";
				break;
			case 12:
				replace_file << "00100010 00100010 00100010";
				break;
			case 13:
				replace_file << "00110011 00110011 00110011";
				break;
			case 14:
				replace_file << "01000100 01000100 01000100";
				break;
			case 15:
				replace_file << "01010101 01010101 01010101";
				break;
			case 16:
				replace_file << "01100110 01100110 01100110";
				break;
			case 17:
				replace_file << "01110111 01110111 01110111";
				break;
			case 18:
				replace_file << "10001000 10001000 10001000";
				break;
			case 19:
				replace_file << "10011001 10011001 10011001";
				break;
			case 20:
				replace_file << "10101010 10101010 10101010";
				break;
			case 21:
				replace_file << "10111011 10111011 10111011";
				break;
			case 22:
				replace_file << "11001100 11001100 11001100";
				break;
			case 23:
				replace_file << "11011101 11011101 11011101";
				break;
			case 24:
				replace_file << "11101110 11101110 11101110";
				break;
			case 25:
				replace_file << "11111111 11111111 11111111";
				break;
			case 26:
				replace_file << "10010010 01001001 00100100";
				break;
			case 27:
				replace_file << "01001001 00100100 10010010";
				break;
			case 28:
				replace_file << "00100100 10010010 01001001";
				break;
			case 29:
				replace_file << "01101101 10110110 11011011";
				break;
			case 30:
				replace_file << "10110110 11011011 01101101";
				break;
			case 31:
				replace_file << "11011011 01101101 10110110";
				break;
			case 32:
				replace_file << random_binary();
				break;
			case 33:
				replace_file << random_binary();
				break;
			case 34:
				replace_file << random_binary();
				break;
			case 35:
				replace_file << random_binary();
				break;
			default:
				return false;
			}
			count++;
		}
		replace_file.close();
		if (replace_file.is_open() == true)return false;
		else return true;
	}
	catch (std::exception &e)
	{
		//Need a GUI developer to display it in a list box for the file which is not processed well
		//These exceptions are most unlikely to occur but will help the 
		//customers to notify us
		std::cout << "Exception thrown out" <<e.what() <<std::endl;
		wxMessageBox("Test", e.what());
		return false;
	}
}

void Scanner::secure_pass(std::wstring file_location,int pass)
{
	for (int i = 0; i < pass; i++)replace_file(file_location);
	//Finally we want to rename and remove the file, that is important
	if (std::ifstream(file_location))
	{
		boost::filesystem::path current_path(file_location);
		boost::filesystem::path CD = current_path.parent_path();
		std::string cd = CD.string();
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::string file_loc = converter.to_bytes(file_location);
		std::string encrypt = sha512(file_loc);
		std::string new_path = cd +"//"+ encrypt;
		int status = std::rename(file_loc.c_str(), new_path.c_str());
		if (status == 0)remove(new_path.c_str());
	}
}

// this method is used to return random binary data
std::string random_binary()
{
	std::string random_data = "";
	for (int i = 0; i < 6; i++)
	{
		int ran = std::rand() % (0 + 2);
		random_data += std::to_string(ran);
	}
	return random_data;
}

//This scan will destroy the whole directory which may not be recovered at any cause.
// This feature(removing multiple files) at a time is currently being dis-abled,
// Because it replaces the contents of file with different binary content which works
// quiet similar like encryption since we are removing multiple files and the application
// shows the behaviour of encrypting multiple files, some anti-virus detects this ability as a malware
// But sooner we will get white-listed and this feature will be included.
bool Gutmann::scan(const wchar_t * sDir)
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
			// If this is a file
			else 
			{
				std::wstring file_location = wide_char_to_wide_string(current_path);
				std::cout << "removing : " << file_location;
				secure_pass(file_location);
				// We will increment the deleted file count
				file_count++;
			}
		}
	} while (FindNextFile(hFind, &find_file));

	FindClose(hFind);
	return true;
}
