// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<iostream>
#include<map>
#include<list>
#include<set>
#include"scanner.h"
#include"utilities.h"
#include<boost\filesystem.hpp>
// Analysing the autorun.inf file is a crucial part in protecting the USB drive


template<typename autoruns>
class Autorun:public Scanner
{
private:
	//Autorun Files
	int autorun_id = 0;
	std::map<int, autoruns> autorun_files;
	// List of extensions of the files to check => valid extension list will contain the 
	// extensions present in the inf file
	std::set<std::string> valid_extensions_list;
	// List of sizes of the files to check for scanning
	std::set<long double> size_list;
	// List of hashes for the files present in the autorun
	std::set<std::string> hash_list;
	// located autorun id
	int located_autorun_id = 0;
	// located autorun_list
	std::map<int, autoruns> autorun_file_list;
	// calculate the list of files count

public:
	// Our scanner for scannig of the files
	bool scan(const wchar_t* sDir);
	// This method will gives the locations of files present in the autorun.inf
	bool add_autorun_executables(std::string drive);
	//Check whether the list is empty or not
	bool check_autorun_file();
	// This method will get the hashes for the location of the files
	// may we call it internally after the add_autorun_executables function
	void get_hashes();
	// This method will find whether the file in PC is contained in autorun.inf
	bool check_this_file(std::string hash);
	// This method will locate the files present in the autorun.inf to the other parts of the computer
	void locate();
	// Display all the autroun files in the computer
	void display();
};
