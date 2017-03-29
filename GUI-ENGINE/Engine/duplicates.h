// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<set>
#include<map>
#include<list>
#include"scanner.h"
#include"extensions.h"
#include"sqlite_modern_cpp.h"
using namespace sqlite;

// Tested its working and works well how-ever unit-testing will add power to this algorithm
#include "Callbacks.h"


template<typename duplicates>
class Duplicates :public Scanner
{
private:
	long int file_count = 0;//scanned file count
	int duplicate_file_count = 0;//no of duplicates
	//Preliminary scan
	std::map<long double, duplicates> duplicate_file_sizes;//files with duplicate sizes -checker
	std::set<duplicates> duplicate_sizes_loc;//duplicate file sizes location
	//Confirmatiry test
	std::map<std::string,duplicates> hash_checker; //Check for MD5 signatures
	std::set<duplicates> hash_test_results;  // Final hash list
	//get the results
	std::list<duplicates> final_report;

    MalwareScan_OnStatus OnStatus;
    void* OnStatusContext;
    MalwareScan_OnError OnError;
    void* OnErrorContext;
    IsStopped isStopped;
    void* IsStoppedContext;
    MalwareScan_OnNewDupFile OnNewFile;
    void *OnNewFileContext;

    void Init();
public:
	Duplicates(); // used in initialization for adding information to the database
    Duplicates(MalwareScan_OnStatus OnStatus, void* OnStatusContext,
        MalwareScan_OnError OnError, void* OnErrorContext,
        IsStopped isStopped, void* IsStoppedContext);

	bool scan(const wchar_t * sDir); // scanning for the files
	bool is_extension_suited(std::string extension); // checking whether the extension matches
	bool file_size_checker(long double size, duplicates file_path);
	void find_the_duplicates();
	std::string compute_hash(duplicates file_loc); // computing the md5 hash of the file
	bool check_hash_signatures(std::string hash, duplicates loc); // if the hash is matched add the file-locations to the heap
	void get_duplicates(); //This function needs to be modified by a GUI Developer
	long int get_file_count();  // get the scanned files count
	int get_duplicates_count(); // get the duplicate files count
	void end(); // end the program using

    void SetOnNewFile(MalwareScan_OnNewDupFile OnNewFile, void* OnNewFileContext);
};
