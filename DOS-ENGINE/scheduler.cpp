#include "scheduler.h"
// SWAMI KARUPPASWAMI THUNNAI

bool Scheduler::schedule_this_location(std::string location)
{
	try
	{
		locations.insert(location);
		return true;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
		return false;
	}
	return false;
}
