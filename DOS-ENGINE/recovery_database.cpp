// SWAMI KARUPPASWAMI THUNNAI

#include"recovery.h"
#include"sqlite_modern_cpp.h"

using namespace sqlite;
// Default constructor -used to add information about the process has been started
// into the database
template<typename recovers>
Recovery<recovers>::Recovery()
{
	std::string date_and_time = get_time();
	try
	{
		database d_database("maintainer//CyberGod Maintainer.db");
		d_database <<
			"create table if not exists RECOVERY("
			"Status TEXT,"
			"Time BLOB"
			");";
		d_database << "insert into RECOVERY (Status,Time) values(?,?);"
			<< u"Recovery process has been started"
			<< date_and_time;
	}
	catch (std::exception &e)
	{
		//Need a message box displayed here - GUI Developer wanted for this task
		std::cout << "Exception is thrown out :" << e.what();
	}
}


// Finalize the recovery process
template<typename recovers>
void Recovery<recovers>::end()
{
	std::string date_and_time = get_time();
	try
	{
		database d_database("maintainer//CyberGod Maintainer.db");
		d_database <<
			"create table if not exists RECOVERY("
			"Status TEXT,"
			"Time BLOB"
			");";
		d_database << "insert into RECOVERY (Status,Time) values(?,?);"
			<< u"Recovery process has been completed"
			<< date_and_time;
	}
	catch (std::exception &e)
	{
		//Need a message box displayed here - GUI Developer wanted for this task
		std::cout << "Exception is thrown out :" << e.what();
	}
}

template class Recovery<std::wstring>;