// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<set>

template<typename strings>
class Strings
{
private:
	std::string copyright = "strings v0.1 (C) VISWESWARAN NAGASIVAM";
	std::set<std::string> present_strings;
	char string_list1[52] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	char string_list2[10] = { '0','1','2','3','4','5','6','7','8','9' };
	char string_list3[24] = { '!','@','#','$','%','^','&','*','(',')','_','-','+','=','|','.','/','?',':',';','"',',','<','>' };
	int Choice = 0;
public:
	void get_strings(strings location);
	bool is_ascii(std::string ascii_string);
	void set_choice(int choice);
	std::set<std::string> return_strings();
};

