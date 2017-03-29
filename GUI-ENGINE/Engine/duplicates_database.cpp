// SWAMI KARUPPASWAMI THUNNAI

#include<Windows.h>
#include<ctime>
#include<iomanip>
#include<exception>
#include"conversions.h"
#include "duplicates.h"
#include<boost\filesystem.hpp>
#include"headers.h"

// This is a constructor this will add the process started information to the database
// This can be used for the future reference


template<typename duplicates>
void Duplicates<duplicates>::Init()
{
    std::string date_and_time = get_time();
    try
    {
        if (OnStatus)
        {
            OnStatus(OnStatusContext, L"Creating database...");
        }

        database d_database("maintainer//CyberGod Maintainer.db");
        d_database <<
            "create table if not exists DUPEREMOVER ("
            "Status TEXT,"
            "Time BLOB,"
            "Process TEXT"
            ");";
        d_database << "insert into DUPEREMOVER (Status,Time,Process) values(?,?,?);"
            << u"Process Started"
            << date_and_time
            << u"Duplicate files finding process started";
    }
    catch (std::exception &e)
    {
        //Need a message box displayed here - GUI Developer wanted for this task        
        if (OnError)
        {
            std::string temp(e.what());
            std::wstring errorText(temp.begin(), temp.end());
            OnError(OnErrorContext, errorText.c_str(), 3);
        }
    }
}

template<typename duplicates>
Duplicates<duplicates>::Duplicates()
{
    OnStatus = NULL;
    OnStatusContext = NULL;
    OnError = NULL;
    OnErrorContext = NULL;
    isStopped = NULL;
    IsStoppedContext = NULL;
    OnNewFile = NULL;
    OnNewFileContext = NULL;

    Init();	
}

template<typename duplicates>
Duplicates<duplicates>::Duplicates(MalwareScan_OnStatus OnStatus, void* OnStatusContext,
    MalwareScan_OnError OnError, void* OnErrorContext,
    IsStopped isStopped, void* IsStoppedContext)
{
    this->OnStatus = OnStatus;
    this->OnStatusContext = OnStatusContext;
    this->OnError = OnError;
    this->OnErrorContext = OnErrorContext;
    this->isStopped = isStopped;
    this->IsStoppedContext = IsStoppedContext;
    OnNewFile = NULL;
    OnNewFileContext = NULL;

    Init();
}

template<typename duplicates>
void Duplicates<duplicates>::SetOnNewFile(MalwareScan_OnNewDupFile OnNewFile, void* OnNewFileContext)
{
    this->OnNewFile = OnNewFile;
    this->OnNewFileContext = OnNewFileContext;
}

template<typename duplicates>
void Duplicates<duplicates>::end()
{
	std::string date_and_time = get_time();
	try
	{
		database d_database("maintainer//CyberGod Maintainer.db");
		d_database <<
			"create table if not exists DUPEREMOVER ("
			"Status TEXT,"
			"Time BLOB,"
			"Process TEXT"
			");";
		d_database << "insert into DUPEREMOVER (Status,Time,Process) values(?,?,?);"
			<< u"Process Ended"
			<< date_and_time
			<< u"Duplicate files finding process has been completed successfully";
		std::string files_scanned = std::to_string(file_count); //Total no of files
		std::string dupe_found = std::to_string(duplicate_file_count); // Total no of duplicates
		d_database << "insert into DUPEREMOVER (Status,Time,Process) values(?,?,?);"
			<< u"Files scanned: "
			<< date_and_time
			<< files_scanned;
		d_database << "insert into DUPEREMOVER (Status,Time,Process) values(?,?,?);"
			<< u"Duplicates Found: "
			<< date_and_time
			<< dupe_found;
	}
	catch (std::exception &e)
	{
		//Need a message box displayed here - GUI Developer wanted for this task
        if (OnError)
        {
            std::string temp(e.what());
            std::wstring errorText(temp.begin(), temp.end());
            OnError(OnErrorContext, errorText.c_str(), 3);
        }
	}
}

template class Duplicates<std::wstring>;