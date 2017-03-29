// SWAMI KARUPPASWAMI THUNNAI

//#include<Python.h>

#include<Windows.h>
#include "scanner.h"
#include"conversions.h"
#include"extensions.h"
#include"md5.h"
#include <boost/filesystem.hpp>

bool Scanner::scan(const wchar_t *sDir)
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
			else {
				std::wcout << current_path;
			}
		}
	} while (FindNextFile(hFind, &find_file)); 

	FindClose(hFind); 

	return true;
}

std::string Scanner::get_time()
{
	time_t _timex = time(NULL);
	struct tm * current_time = localtime(&_timex);
	std::string date_and_time = asctime(current_time);
	return date_and_time;
}





