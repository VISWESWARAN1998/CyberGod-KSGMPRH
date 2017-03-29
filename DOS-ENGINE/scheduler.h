// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<iostream>
#include<string>
#include<set>
#include<exception>


class Scheduler
{
private:
	std::set<std::string> locations;
public:
	bool schedule_this_location(std::string location);
};
