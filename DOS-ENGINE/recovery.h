// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include"scanner.h"

template<typename recovers>
class Recovery:public Scanner
{
private:
	const wchar_t* recycle_bin;
	recovers recovery_directory_location;
public:
	Recovery(); //Default constructor to add stuffs to the database
	Recovery(recovers drive_letter,recovers recovery_location);
	bool scan(const wchar_t* sDir);
	bool non_user_file_scan(const wchar_t* sDir);
	bool is_safe_recoverable_format(std::string extension);
	void end();
};
