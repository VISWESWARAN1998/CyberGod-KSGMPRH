// SWAMI KARUPPASWAMI THUNNAI
#pragma once

#include<string>
#include <windows.h>
#include <Wincrypt.h>


bool utilityRemove(std::string file_location);
// the above same functionality implemented for unicode support
bool utilityRemove(std::wstring file_location);
std::string getSizeofRam();
void process();

int get_drive_status(std::string strDriveName);
// get md5 of the file with the ascii file names
std::string get_md5(std::string file_location);

//general logger which saves the log
void logger(std::string time, std::string info);

// calculate the md5 hash of the file for the files with the unicode names
std::string calculate_md5(std::wstring file_location);