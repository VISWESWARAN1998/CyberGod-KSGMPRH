// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include"scanner.h"

// Unicode support added and the feature is not unit tested!

class Gutmann :public Scanner
{
private:
	int file_count = 0;
	int dir_count = 0;
public:
	// Used to remove the entire directory
	bool scan(const wchar_t* sDir);
};
