// SWAMI KARUPPASWAMI THUNNAI

#include"strings.h"
#include"sqlite_modern_cpp.h"
#include"export.h"
#include<exception>
using namespace sqlite;
// eport this only for the first time to make sure that the database is in working condition
// Make sure it is not inside in any of the loops
void init()
{
	database db("strings.db");
	try 
	{
		db << "create table if not exists strings (string text primary key not null,name text);";
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
}

// This is the method which is actually going to find whether the string is present in the
// database or not
bool is_string_present(int choice,std::wstring location)
{
	Strings<std::wstring> obj;
	obj.set_choice(choice);
	obj.get_strings(location);
	std::set<std::string> strings = obj.return_strings();
	typedef std::set<std::string>::iterator iterator;
	iterator itr1 = strings.begin();
	iterator itr2 = strings.end();
	database db("strings.db");
	bool status = false;
	for (iterator itr = itr1; itr != itr2; ++itr)
	{
		try {
			db << "select string from strings where string=?"<<*itr
				>> [&](std::unique_ptr<std::string> str) {
				if (str != nullptr)
				{
					status = true;
				}
			};
			if (status == true)break;
		}
		catch (std::exception &e)
		{
			std::cout << e.what();
		}

	}
	return status;
}