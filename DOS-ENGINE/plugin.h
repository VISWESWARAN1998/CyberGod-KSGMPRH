#pragma once
// SWAMI KARUPPASWAMI THUNNAI
#include<string>
#include<list>
class Plugin
{
private:
	std::list<std::string> available_plugins;
public:
	void get_available_plugins();
	bool execute_plugin(std::string location,int argc,wchar_t** argv);
};