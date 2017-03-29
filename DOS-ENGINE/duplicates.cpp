// SWAMI KARUPPASWAMI THUNNAI
#include<Windows.h>
#include<ctime>
#include<iomanip>
#include<exception>
#include<codecvt>
#include"conversions.h"
#include "duplicates.h"
#include<boost\filesystem.hpp>
#include<wx\msgdlg.h>
#include"utilities.h"
#include"headers.h"
#include"html.h"


template<typename duplicates>
bool Duplicates<duplicates>::scan(const wchar_t * sDir)
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
				duplicates Path = wide_char_to_wide_string(current_path);
				//wxMessageBox(Path, Path);
				boost::filesystem::path p = { Path };
				// we got the extension of the file
				std::string extension = p.extension().string();
				// we need file name too
				duplicates name_of_file = p.filename().wstring();
				bool can_scan = is_extension_suited(extension);
				//and also the file size
				long double size = file_size(p);
				// If the file can be scanned
				if (can_scan == true)
				{
					std::cout << "Scanning " << name_of_file << "\t";
					std::cout << "Size : " << size << "\n";
					file_size_checker(size, Path);
					std::cout << "\nPath " << Path << "\n";
				}
				file_count++;
			}
		}
	} while (FindNextFile(hFind, &find_file));
	FindClose(hFind);
	return true;
}

template<typename duplicates>
bool Duplicates<duplicates>::is_extension_suited(std::string extension)
{
	Extensions check_extensions;
	if (check_extensions.is_image(extension) == true)return true;
	else if (check_extensions.is_media(extension) == true)return true;
	else if (check_extensions.is_document(extension) == true)return true;
	else return false;
	return false;
}
template<typename duplicates>
bool Duplicates<duplicates>::file_size_checker(long double size, duplicates file_path)
{
	file_count++;//Increment the scanned files count
	std::map<long double, duplicates>::iterator itr = duplicate_file_sizes.find(size);
	if (itr == duplicate_file_sizes.end())
	{
		duplicate_file_sizes[size] = file_path;
		return false;
	}
	else
	{
		std::set<duplicates>::iterator add_file_sizes = duplicate_sizes_loc.find(file_path);
		std::set<duplicates>::iterator add_file_sizesx = duplicate_sizes_loc.find(itr->second);
		if (add_file_sizes == duplicate_sizes_loc.end())duplicate_sizes_loc.insert(file_path);
		if (add_file_sizesx == duplicate_sizes_loc.end())duplicate_sizes_loc.insert(itr->second);
		return true;
	}
}

// once the files with duplicates sizes has been obtained this method
// will be used to get the hashes for each of the file and schedule for further processing

template<typename duplicates>
void Duplicates<duplicates>::find_the_duplicates()
{
	std::set<duplicates>::iterator itr1 = duplicate_sizes_loc.begin();
	std::set<duplicates>::iterator itr2 = duplicate_sizes_loc.end();
	for (std::set<duplicates>::iterator itr = itr1; itr != itr2; itr++)
	{
		std::string Hash = compute_hash(*itr);
		std::cout << Hash << std::endl;
		if(Hash!="failed")check_hash_signatures(Hash, *itr);
	}
}

// This function is used to calculate the windows dependent MD5 hash
template<typename duplicates>
std::string Duplicates<duplicates>::compute_hash(duplicates file_loc)
{
	std::string hash = calculate_md5(file_loc);
	return hash;
}

//This method is meant for checking whether the hash matches
// If the hash has been matched then get the location of duplicates
template<typename duplicates>
bool Duplicates<duplicates>::check_hash_signatures(std::string hash, duplicates loc)
{
	std::map<std::string, duplicates>::iterator itr = hash_checker.find(hash);
	if (itr == hash_checker.end())hash_checker[hash] = loc;
	else
	{
		std::set<duplicates>::iterator final_check = hash_test_results.find(loc);
		std::set<duplicates>::iterator final_checkx = hash_test_results.find(itr->second);
		if (final_check == hash_test_results.end())hash_test_results.insert(loc);
		if (final_checkx == hash_test_results.end())hash_test_results.insert(itr->second);
		return true;
	}
	return false;
}


template<typename duplicates>
void Duplicates<duplicates>::get_duplicates()
{
	std::set<duplicates>::iterator itr1 = hash_test_results.begin();
	std::set<duplicates>::iterator itr2 = hash_test_results.end();
	HTML html;
	html.create_file(L"duplicates.html", "Duplicate files finder", "NULL");
	for (std::set<duplicates>::iterator itr = itr1; itr != itr2; itr++)
	{
		duplicate_file_count++;//
		std::cout <<" [DUPLICATE]: " <<*itr << "\n";
		html.document(L"p", *itr);
	}
	html.finalize_html();
	// end the duplicates in the database
	end();
}


// For the ease of the GUI developer 

//This method will get the no of files scanned

template<typename duplicates>
long int Duplicates<duplicates>::get_file_count()
{
	return file_count;
}

// This method will return the total no of duplicates
template<typename duplicates>
int Duplicates<duplicates>::get_duplicates_count()
{
	return duplicate_file_count;
}

template class Duplicates<std::wstring>;



