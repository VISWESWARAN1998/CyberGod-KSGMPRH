// SWAMI KARUPPASWAMI THUNNAI
#include "conversions.h"
#include<Windows.h>
std::string wide_char_to_string(wchar_t* wide)
{
	std::wstring wide_string(wide);
	std::string str(wide_string.begin(), wide_string.end());
	return str;
}


const wchar_t * string_wide_pointer(std::string input)
{
	std::wstring wide_string(input.begin(), input.end());//Make it as a wide string
	const wchar_t* output = wide_string.c_str();
	return output;
}

std::wstring wide_char_to_wide_string(wchar_t * wide)
{
	std::wstring wide_string(wide);
	return wide_string;
}

std::string to_utf8(const std::wstring & str)
{
	std::string ret;
	int len = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0, NULL, NULL);
	if (len > 0)
	{
		ret.resize(len);
		WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), &ret[0], len, NULL, NULL);
	}
	return ret;
}

