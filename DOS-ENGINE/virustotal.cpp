// SWAMI KARUPPASWAMI THUNNAI
#include "virustotal.h"
#include"utilities.h"
#include<thread>
#include<Python.h>
#include<boost\filesystem.hpp>

bool VirusTotal::scan_from_log(std::wstring file)
{
	typedef std::set<std::wstring>::iterator iterator;
	bool is_information_gathered = extract_information(file);
	if (is_information_gathered == true)
	{
		// If all the information is gathered then we are going to process the data
		iterator itr1 = informations_from_log.begin();
		iterator itr2 = informations_from_log.end();
		for (iterator itr = itr1; itr != itr2; ++itr)
		{
			// we are iterating over the files. Check whether the file exists or not
			if (is_file_present(*itr) == true)
			{
				boost::filesystem::path path = *itr;
				std::string extension = path.extension().string();
				std::string file_name = path.filename().string();
				if (is_common_extension(extension) == true)
				{
					std::cout << "scanning for " << file_name<<"\n";
					std::string hash = calculate_md5(*itr);
					std::thread start(scan_for_virustotal, hash);
					start.join();
				}
				else std::cout << "[UNWANTED - NOT SCANNED]: " << file_name << "\n";
			}
		}
	}
	return false;
}

bool VirusTotal::is_file_present(std::wstring location)
{
	if (std::ifstream(location))return true;
	return false;
}

void scan_for_virustotal(std::string hash)
{
	std::string md5 = hash;
	if (md5 != "failed")
	{
		try {
			std::string scan = "Hunter.scan(\"" + md5 + "\")";
			// We should call our Python function here
			Py_Initialize();
			PyRun_SimpleString("import sys; sys.path.append('.')");
			PyRun_SimpleString("import Hunter;");
			PyRun_SimpleString(scan.c_str());
			Py_Finalize();
			std::cout << "JSON: " << md5 << ".json\n";
		}
		catch (std::exception &e) {
			std::cout << e.what() << "\n";
		}
	}
}
