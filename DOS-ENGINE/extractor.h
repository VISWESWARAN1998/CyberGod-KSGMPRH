// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<set>
// This class will extract the information present in the log file

class Extractor
{
protected:
	std::set<std::wstring> informations_from_log;
public:
	bool extract_information(std::wstring file);
};
