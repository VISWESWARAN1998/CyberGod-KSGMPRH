// This is going to add efficiency to the virus-total results
#pragma once
#include"extractor.h"
#include"extensions.h"

/*
This class will have the functionality of scanning the entire drive with virus total
Scanning the locations from the log files
*/

class VirusTotal:public Extractor,Extensions
{
public:
	// scans from the log
	bool scan_from_log(std::wstring file);
	// checking whether the file exists or not
	bool is_file_present(std::wstring location);
};



void scan_for_virustotal(std::string hash);