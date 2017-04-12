// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<iostream>
#include<string>
#include<exception>
#include<boost\filesystem.hpp>
#include"sqlite_modern_cpp.h"
// This class is meant for verifying the files
// which has been shipped along with CyberGod KSGMPRH's binary
class Verifyier
{
private:
	std::string hash_of_file;
	double size_of_file;
	int id;
public:
	Verifyier(int ID);
	// Check whether the files are to be processed further
	void can_process_further();
	// a method used to handle the invalid ID
	void handle_invalid_id();
	// This method is used to update the hashes and sizes
	bool update_hashes_and_size(int id,std::string hash, int size);
};

void boot_loader();