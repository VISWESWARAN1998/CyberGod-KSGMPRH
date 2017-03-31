// SWAMI KARUPPASWAMI THUNNAI
#include"strings.h"
template<typename strings>
inline void Strings<strings>::get_strings(strings location)
{
	if (std::ifstream(location))
	{
		std::ifstream open_location;
		open_location.open(location,std::ios::binary);
		if (open_location.is_open())
		{
			while (true)
			{
				std::string string;
				open_location >> string;
				if (string.size() >= Choice)
				{
					if (is_ascii(string))present_strings.insert(string);
				}
				if (open_location.eof())break;
			}
			open_location.close();
		}
	}
}

template<typename strings>
bool Strings<strings>::is_ascii(std::string ascii_string)
{
	for (int i = 0; i < ascii_string.size(); i++)
	{
		bool match = false;
		for (int character = 0; character < 52; character++)if (ascii_string[i] == string_list1[character])match = true;
		for (int numbers = 0; numbers < 10; numbers++)if (ascii_string[i] == string_list2[numbers])match = true;
		for (int specials = 0; specials < 24; specials++)if (ascii_string[i] == string_list3[specials])match = true;
		if (match == false)return false;
	}
	return true;
}

// This method is used to set the minimum length of the string
template<typename strings>
void Strings<strings>::set_choice(int choice=0)
{
	Choice = choice;
}

template<typename strings>
std::set<std::string> Strings<strings>::return_strings()
{
	return present_strings;
}





template class Strings<std::wstring>;
