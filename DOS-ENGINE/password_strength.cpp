// SWAMI KARUPPASWAMI THUNNAI

#include "password_check.h"

PasswordCheck::PasswordCheck(std::string password)
{
	length_of_password = password.size();
	for (int i = 0; i < length_of_password; i++)
	{
		if (isalpha(password[i]))
		{
			if (isupper(password[i]))
			{
				count_of_captials++;
				capitals = true;
			}
			if (islower(password[i]))
			{
				count_of_lowers++;
				lowers = true;
			}
		}
		else if (isdigit(password[i]))
		{
			count_of_numericals++;
			numbers = true;
		}
		else if (password[i] == ' ')
		{
			count_of_whitespaces++;
			spaces = true;
		}
		else
		{
			count_of_special++;
			specials = true;
		}

	}
}

long double PasswordCheck::return_guess_count()
{
	// formula = password length^password character type
	int power = 0;
	int base = (COUNT_OF_UPPER*count_of_captials) + (COUNT_OF_LOWER*count_of_lowers) + (COUNT_OF_NUMBERS*count_of_numericals) + (COUNT_OF_SPECIALS*count_of_special);
	if (capitals)
	{
		power++;
	}
	if (lowers)
	{
		power++;
	}
	if (numbers)
	{
		power++;
	}
	if (spaces)
	{
		power++;
	}
	if (specials)
	{
		power++;
	}
	long double guess = pow(base, power);
	return guess;
}

int PasswordCheck::get_capital_count() { return count_of_captials; }
int PasswordCheck::get_lower_count() { return count_of_lowers; }
int PasswordCheck::get_number_count() {
	return count_of_numericals;
}
int PasswordCheck::get_symbol_count() { return count_of_special; }
int PasswordCheck::get_whitespace_count() { return count_of_whitespaces; }


