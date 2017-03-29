// SWAMI KARUPPASWAMI THUNNAI
#include "utilities.h"
#include<Windows.h>
#include<iostream>
#include<fstream>
#include <cstring>
#include <sstream>
#include<thread>
#include<mutex>
#include<boost\lexical_cast.hpp>
#include<wx\msgdlg.h>
#include"md5.h"

/*
This source file contains mostly, non-object oriented method defitions,
This is created beacause this is widely used in almost all parts of the software
so the we can use it without creating any objects and thereby making the code more complex
*/

#define DRIVE_UNKNOWN 0
#define DRIVE_NO_ROOT_DIR 1
#define DRIVE_REMOVABLE 2
#define DRIVE_FIXED 3
#define DRIVE_REMOTE 4
#define DRIVE_CDROM 5
#define DRIVE_RAMDISK 6
#define BUFSIZE 1024
#define MD5LEN  16



// This will return the size of the ram in string may be we can convert it into int
// for our useage...
std::string getSizeofRam()
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);

	std::ostringstream strs;
	strs << (double)status.ullTotalPhys / (1024 * 1024 * 1024);
	std::string strRamSize = strs.str();
	double size = boost::lexical_cast<double>(strRamSize);
	// rounding off the decimal vallues to get the proper information
	int ramSize = round(size);
	std::string ram_size = std::to_string(ramSize);
	return ram_size;

}

// Regular removal of file used in various part of our program we need not any classes
// Encapsulation is not needed for this - It makes the stuff more complex
bool utilityRemove(std::string file_location)
{
	if (std::ifstream(file_location))
	{
		remove(file_location.c_str());
		return true;
	}
	return false;
}

// The above same function which supports unicode =>method overloading
// Regular removal of file used in various part of our program we need not any classes
// Encapsulation is not needed for this - It makes the stuff more complex
bool utilityRemove(std::wstring file_location)
{
	if (std::ifstream(file_location))
	{
		DeleteFile(file_location.c_str());
		return true;
	}
	return false;
}

// Void process completion message

void process()
{
	wxMessageBox("The process has been completed successfully", "CyberGod KSGMPRH", wxOK | wxCENTER);
}

//This function is used to get the status of the drive

int get_drive_status(std::string strDriveName)
{
	std::wstring drive(strDriveName.length(), L' ');
	std::copy(strDriveName.begin(), strDriveName.end(), drive.begin());
	LPCWSTR data;
	data = (LPCWSTR)drive.c_str();
	UINT rval = GetDriveType(data);
	if (DRIVE_REMOVABLE == rval)return 2; // Removable drive
	if (DRIVE_CDROM == rval)return 5; // CD drive
	if (DRIVE_FIXED == rval)return 3;//Fixed drive
	if (DRIVE_RAMDISK == rval)return 6; //RAM
	if (DRIVE_REMOTE == rval)return 4;//Remote drives
	if (DRIVE_UNKNOWN == rval)return 0; // Unknown drive
	if (DRIVE_NO_ROOT_DIR == rval)return 1; // Drive no root directory
}


// Used to get the MD5 of the file - This method is being used by various classes so
// I consider it will be useful to call it whenever one needs without the need of creating 
//objects or inheriting the whole class for just to use this facility
std::string get_md5(std::string file_location)
{
	char *cstr = new char[file_location.length() + 1];
	strcpy(cstr, file_location.c_str());
	// do stuff
	std::string hash = CALL_MD5_Function(cstr);
	delete[] cstr;
	return hash;
}

// IMPORTANT : LOGGER for our entire software => must be thread safe

void logger(std::string time,std::string info)
{
	// we just need to protect this four lines of code
	try 
	{
		std::ofstream file;
		file.open("console.log", std::ios::app);
		file << time << info << "\n";
		file.close();
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
}

std::string calculate_md5(std::wstring file_location)
{
	DWORD dwStatus = 0;
	BOOL bResult = FALSE;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	HANDLE hFile = NULL;
	BYTE rgbFile[BUFSIZE];
	DWORD cbRead = 0;
	BYTE rgbHash[MD5LEN];
	DWORD cbHash = 0;
	CHAR rgbDigits[] = "0123456789abcdef";
	LPCWSTR filename = file_location.c_str();
	// Logic to check usage goes here.

	hFile = CreateFile(filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		dwStatus = GetLastError();
		//printf("Error opening file %s\nError: %d\n", filename,
		//dwStatus);
		return "failed";
	}

	// Get handle to the crypto provider
	if (!CryptAcquireContext(&hProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT))
	{
		dwStatus = GetLastError();
		//printf("CryptAcquireContext failed: %d\n", dwStatus);
		CloseHandle(hFile);
		return "failed";
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
	{
		dwStatus = GetLastError();
		//printf("CryptAcquireContext failed: %d\n", dwStatus);
		CloseHandle(hFile);
		CryptReleaseContext(hProv, 0);
		return "failed";
	}

	while (bResult = ReadFile(hFile, rgbFile, BUFSIZE,
		&cbRead, NULL))
	{
		if (0 == cbRead)
		{
			break;
		}

		if (!CryptHashData(hHash, rgbFile, cbRead, 0))
		{
			dwStatus = GetLastError();
			//printf("CryptHashData failed: %d\n", dwStatus);
			CryptReleaseContext(hProv, 0);
			CryptDestroyHash(hHash);
			CloseHandle(hFile);
			return "failed";
		}
	}

	if (!bResult)
	{
		dwStatus = GetLastError();
		printf("ReadFile failed: %d\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		CloseHandle(hFile);
		return "failed";
	}

	cbHash = MD5LEN;
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
	{
		std::string hash;
		//printf("MD5 hash of file %s is: ", filename);
		for (DWORD i = 0; i < cbHash; i++)
		{
			hash += rgbDigits[rgbHash[i] >> 4];
			hash += rgbDigits[rgbHash[i] & 0xf];
		}
		//std::cout << hash;
        CloseHandle(hFile);
		return hash;
		printf("\n");
	}
	else
	{
		dwStatus = GetLastError();
		//printf("CryptGetHashParam failed: %d\n", dwStatus);
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	CloseHandle(hFile);
	return "failed";
}
