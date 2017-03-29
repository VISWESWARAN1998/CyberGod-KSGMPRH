// SWAMI KARUPPASWAMI THUNNAI

#include<iostream>
#include<Windows.h>
#include<boost\filesystem.hpp>
#include<boost\algorithm\string.hpp>
#include<Python.h>
#include"plugin.h"



void Plugin::get_available_plugins()
{
	if (std::ifstream("cybergod.plugins"))
	{
		std::ifstream file;
		file.open("cybergod.plugins");
		while (!file.eof())
		{
			std::string locations;
			std::getline(file, locations);
			if (locations != "")
			{
				boost::algorithm::trim_right(locations);
				boost::algorithm::trim_left(locations);
				std::cout << locations;
				available_plugins.push_back(locations);
			}
		}
	}
	else
	{
		MessageBeep(700);
		MessageBox(NULL, L"Create locations file and start adding your plugins", L"CyberGod KSGMPRH - locations not found", MB_OK);
	}
}

// This method is used to execute a plugin actuallty
// It is so very important for the developers

bool Plugin::execute_plugin(std::string location,int argc,wchar_t** argv)
{
	if (std::ifstream(location))
	{
		
		try {
			const char* file_location = location.c_str();
			FILE* file_pointer;
			// Initialize the Python interpreter
			Py_Initialize();
			PySys_SetArgv(argc, argv);
			file_pointer = _Py_fopen(file_location, "r");
			// Run the Python file
			PyRun_SimpleFile(file_pointer, file_location);
			// Finalize the Python interpreter
			Py_Finalize();
		}
		catch (...)
		{
			std::cout << "exception";
		}
		return true;
	}
	else
	{
		std::cout << "\nLocation Invalid "<<location;
		return false;
	}
	return false;
}
