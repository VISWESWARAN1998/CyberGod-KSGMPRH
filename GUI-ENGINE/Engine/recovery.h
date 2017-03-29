// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include"scanner.h"

#include "Callbacks.h"

template<typename recovers>
class Recovery:public Scanner
{
private:
	const wchar_t* recycle_bin;
	recovers recovery_directory_location;

    MalwareScan_OnStatus OnStatus;
    void* OnStatusContext;
    MalwareScan_OnError OnError;
    void* OnErrorContext;
    MalwareScan_OnNewDupFile OnRecoveredFile;
    void* OnRecoveredFileContext;    
    IsStopped isStopped;
    void* IsStoppedContext;

    bool CheckIsStopped();
    void InitDatabase();
    void Init(recovers drive_letter, recovers recovery_location);
public:    
	Recovery(); //Default constructor to add stuffs to the database
    Recovery(MalwareScan_OnStatus OnStatus, void* OnStatusContext, MalwareScan_OnError OnError, void* OnErrorContext, IsStopped isStopped, void* IsStoppedContext);
	Recovery(recovers drive_letter,recovers recovery_location);
    Recovery(recovers drive_letter, recovers recovery_location, MalwareScan_OnStatus OnStatus, void* OnStatusContext, MalwareScan_OnError OnError, void* OnErrorContext, MalwareScan_OnNewDupFile OnRecoveredFile, void* OnRecoveredFileContext, IsStopped isStopped, void* IsStoppedContext);
    bool scan(const wchar_t* sDir, int level);
	bool non_user_file_scan(const wchar_t* sDir, int level);
	bool is_safe_recoverable_format(std::string extension);
	void end();
};
