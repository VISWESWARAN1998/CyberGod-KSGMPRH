// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#define COUNT_OF_LOWER 26
#define COUNT_OF_UPPER 26
#define COUNT_OF_NUMBERS 10
#define COUNT_OF_SPECIALS 31
#define WHITE_SPACE 1

#include<iostream>
#include<string>
#include<list>

class PasswordCheck
{
private:
	int count_of_captials=0;
	int count_of_lowers=0;
	int count_of_special=0;
	int count_of_numericals=0;
	int count_of_whitespaces = 0;
	int length_of_password=0;
	bool capitals = false;
	bool lowers = false;
	bool numbers = false;
	bool specials = false;
	bool spaces = false;
	std::list<char> symbols;
	// Used to show the no of gussess needed to crack the password
	long double no_of_guess = 0;
public:
	PasswordCheck(std::string password);
	long double return_guess_count();
	int get_capital_count();
	int get_lower_count();
	int get_number_count();
	int get_symbol_count();
	int get_whitespace_count();
};
