// SWAMI KARUPPASWAMI THUNNAI

#include"recovery.h"
#include"sqlite_modern_cpp.h"

using namespace sqlite;

template<typename recovers>
void Recovery<recovers>::InitDatabase()
{
    std::string date_and_time = get_time();

    if (OnStatus)
    {
        OnStatus(OnStatusContext, L"Creating database...");
    }

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
        // std::cout << "Exception is thrown out :" << e.what();
        if (OnError)
        {
            std::string what(e.what());
            std::wstring strError(what.begin(), what.end());
            OnError(OnErrorContext, strError.c_str(), 11);
        }
    }
}

// Default constructor -used to add information about the process has been started
// into the database
template<typename recovers>
Recovery<recovers>::Recovery()
{    
    OnStatus = NULL;
    OnStatusContext = NULL;
    OnError = NULL;
    OnErrorContext = NULL;
    OnRecoveredFile = NULL;
    OnRecoveredFileContext = NULL;
    isStopped = NULL;
    IsStoppedContext = NULL;

    InitDatabase();	
}

template<typename recovers>
Recovery<recovers>::Recovery(MalwareScan_OnStatus OnStatus, void* OnStatusContext, MalwareScan_OnError OnError, void* OnErrorContext, IsStopped isStopped, void* IsStoppedContext)
{
    this->OnStatus = OnStatus;
    this->OnStatusContext = OnStatusContext;
    this->OnError = OnError;
    this->OnErrorContext = OnErrorContext;
    this->OnRecoveredFile = NULL;
    this->OnRecoveredFileContext = NULL;
    this->isStopped = isStopped;
    this->IsStoppedContext = IsStoppedContext;

    InitDatabase();
}


// Finalize the recovery process
template<typename recovers>
void Recovery<recovers>::end()
{
    std::string date_and_time = get_time();

    if (OnStatus)
    {
        OnStatus(OnStatusContext, L"Finalizing");
    }

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
        //std::cout << "Exception is thrown out :" << e.what();
        if (OnError)
        {
            std::string what(e.what());
            std::wstring strError(what.begin(), what.end());
            OnError(OnErrorContext, strError.c_str(), 11);
        }
    }
}

template class Recovery<std::wstring>;