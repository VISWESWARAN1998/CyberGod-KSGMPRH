// SWAMI KARUPPASWAMI THUNNAI
#include "extractor.h"
#include<exception>


bool Extractor::extract_information(std::wstring file)
{
	std::ifstream input_log;
	input_log.open(file);
	if (input_log.is_open())
	{
		while (!input_log.eof())
		{
			std::string location;
			std::getline(input_log, location);
			try
			{
				std::wstring loc(location.begin(), location.end());
				informations_from_log.insert(loc);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << "\n";
			}
	    }
		input_log.close();
		return true;
	}
	else std::cout << "The file cannot be opened! please check with your input\n";
	return false;
}
