// SWAMI KARUPPASWAMI THUNNAI
#pragma once

#include<string>



//wchar_t* to string converter
std::string wide_char_to_string(wchar_t* wide);

//string to const wchar_t*
const wchar_t* string_wide_pointer(std::string input);

//wchar_t* to wstring conversion
std::wstring wide_char_to_wide_string(wchar_t* wide);

// encode the strings

std::string to_utf8(const std::wstring &str);
