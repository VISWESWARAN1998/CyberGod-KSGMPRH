// SWAMI KARUPPASWAMI THUNNAI

#include"shortcutvirus.h"
#include"sqlite_modern_cpp.h"
#include<wx/msgdlg.h>

using namespace sqlite;
template<typename shortcuts>
ShortCutVirusRemover<shortcuts>::ShortCutVirusRemover()
{
	std::string date_and_time = get_time();
	try
	{
		database d_database("maintainer//CyberGod Maintainer.db");
		d_database <<
			"create table if not exists SHORTCUTVIRUSREMOVER("
			"Status TEXT,"
			"Time BLOB"
			");";
		d_database << "insert into SHORTCUTVIRUSREMOVER (Status,Time) values(?,?);"
			<< u"Process started @"
			<< date_and_time;
	}
	catch (std::exception &e)
	{
		// Display the error message
		wxMessageBox(e.what(), "CyberGod KSGMPRH", wxOK | wxCENTER);
	}
}

template class ShortCutVirusRemover<std::wstring>;
