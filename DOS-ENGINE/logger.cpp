// SWAMI KARUPPASWAMI THUNNAI
#include "logger.h"

// This function is uesd to log information from the file
void logger(std::string file_name, std::wstring information)
{
	std::ofstream log;
	log.open(file_name, std::ios::app);
	if (log.is_open())
	{
		std::string info(information.begin(), information.end());
		log << info << "\n";
		log.close();
	}
	else std::cout << "Logger error " << file_name << " cannot be opened!\n";
}

// This handles the thread
void Log(std::string file_name, std::wstring information)
{
	std::thread t1(logger, file_name, information);
	t1.join();
}