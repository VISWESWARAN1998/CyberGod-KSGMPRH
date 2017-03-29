// SWAMI KARUPPASWAMI THUNNAI
#include <Windows.h>
#include<exception>
#include"extensions.h"
#include"conversions.h"
#include "recovery.h"
#include<boost\filesystem.hpp>
#include<wx/msgdlg.h>


template<typename recovers>
bool Recovery<recovers>::CheckIsStopped()
{
    if (isStopped)
    {
        return isStopped(IsStoppedContext);
    }
    return false;
}


template<typename recovers>
void Recovery<recovers>::Init(recovers drive_letter, recovers recovery_location)
{
    //locating the recycle bin...
    recovers complete_string = drive_letter + "$RECYCLE.BIN";
    //Make it as a wide character...
    std::wstring Path(complete_string.begin(), complete_string.end());
    // we are setting up the path
    recycle_bin = Path.c_str();
    std::wcout << "\n\n" << recycle_bin;
    recovery_directory_location = recovery_location;
    //This will be our default recovery folder
    std::string title = "CyberGod Recovery Data";
    //create our directory here
    boost::filesystem::path directory(recovery_location + title);
    recovery_directory_location = recovery_location + title;

    
    if (!boost::filesystem::is_directory(directory))
    {
        if (boost::filesystem::create_directory(directory))
        {
            //Need a GUI Developer to add this to GUI
            //std::cout << "Directory has been created";
            if (OnStatus)
            {
                OnStatus(OnStatusContext, L"Directory has been created");
            }
        }
        else
        {
            //Need a GUI dev to handle this in GUI
            wxMessageBox("Unable to create the directory on the specified location", "CyberGod KSGMPRH -error");
            return;
        }
    }
    else
    {
        if (OnStatus)
        {
            OnStatus(OnStatusContext, L"Directory is already created");
        }
    }

    if (OnStatus)
    {
        OnStatus(OnStatusContext, L"Scanning recycle bin...");
    }

    scan(recycle_bin, 0);
    const wchar_t* drive_letter_for_dollar_scan = drive_letter.c_str();

    if (OnStatus)
    {
        OnStatus(OnStatusContext, L"Scanning not user files...");
    }

    non_user_file_scan(drive_letter_for_dollar_scan, 0);
}


//Parameterized constructor to set up the recycle bin path
template<typename recovers>
Recovery<recovers>::Recovery(recovers drive_letter,recovers recovery_location)
{
    OnStatus = NULL;
    OnStatusContext = NULL;
    OnError = NULL;
    OnErrorContext = NULL;
    OnRecoveredFile = NULL;
    OnRecoveredFileContext = NULL;
    isStopped = NULL;
    IsStoppedContext = NULL;

    Init(drive_letter, recovery_location);
}

template<typename recovers>
Recovery<recovers>::Recovery(recovers drive_letter, recovers recovery_location, MalwareScan_OnStatus OnStatus, void* OnStatusContext, MalwareScan_OnError OnError, void* OnErrorContext, MalwareScan_OnNewDupFile OnRecoveredFile, void* OnRecoveredFileContext, IsStopped isStopped, void* IsStoppedContext)
{
    this->OnStatus = OnStatus;
    this->OnStatusContext = OnStatusContext;
    this->OnError = OnError;
    this->OnErrorContext = OnErrorContext;
    this->OnRecoveredFile = OnRecoveredFile;
    this->OnRecoveredFileContext = OnRecoveredFileContext;
    this->isStopped = isStopped;
    this->IsStoppedContext = IsStoppedContext;

    Init(drive_letter, recovery_location);
}


// the scanner which has been implemented for the recovering of the files function
template<typename recovers>
bool Recovery<recovers>::scan(const wchar_t * sDir, int level)
{
	WIN32_FIND_DATA find_file;
	HANDLE hFind = NULL;
	wchar_t current_path[2048];
	wsprintf(current_path, L"%s\\*.*", sDir);

    try
    {
        if ((hFind = FindFirstFile(current_path, &find_file)) == INVALID_HANDLE_VALUE)
        {
            if (OnError && level==0)
            {
                wchar_t errorMessage[2048];
                wsprintf(errorMessage, L"Path not found: [%s]\n", sDir);
                OnError(OnErrorContext, errorMessage, 1);
            }
            return false;
        }

        do
        {
            if (wcscmp(find_file.cFileName, L".") != 0
                && wcscmp(find_file.cFileName, L"..") != 0 && !CheckIsStopped())
            {
                wsprintf(current_path, L"%s\\%s", sDir, find_file.cFileName);
                if (find_file.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
                {
                    scan(current_path, level + 1);
                }
                else
                {
                    //This consists of current path
                    recovers Path = wide_char_to_wide_string(current_path);
                    boost::filesystem::path p = { Path };
                    // we got the extension of the file
                    std::string extension = p.extension().string();
                    // we need file name too
                    recovers name_of_file = p.filename().wstring();
                    bool can_scan = is_safe_recoverable_format(extension);
                    //and also the file size
                    long double size = file_size(p);
                    // If the file can be scanned
                    if (can_scan == true)
                    {
                        //std::cout << "Trying to recover "<<name_of_file<<"\n";

                        boost::filesystem::path source(Path);
                        boost::filesystem::path destination(recovery_directory_location + "//" + name_of_file);
                        unsigned long long size = 0;
                        try {
                            boost::filesystem::copy_file(source, destination);
                            size = 1;
                        }
                        catch (std::exception &e)
                        {                            
                            //std::cout << "\nException thrown out :" << e.what() << "\n";                            
                            if (OnError)
                            {
                                std::string what(e.what());
                                std::wstring strError(what.begin(), what.end());
                                OnError(OnErrorContext, strError.c_str(), -1);
                            }
                        }
                        //std::cout << "Recovered " << name_of_file << "\n";
                        if (OnRecoveredFile)
                        {
                            OnRecoveredFile(OnRecoveredFileContext, name_of_file.c_str(), size, L"", 0);
                        }
                    }
                }
            }
        } while (FindNextFile(hFind, &find_file) && !CheckIsStopped());
        FindClose(hFind);
    } 
    catch (std::exception& ex)
    {
        //const char* w = ex.what();
        //std::cout << "\nException thrown out :" << ex.what() << "\n";
        if (OnError)
        {
            std::string what(ex.what());
            std::wstring strError(what.begin(), what.end());
            OnError(OnErrorContext, strError.c_str(), -2);
        }
    }
	return true;	
}


// DEFINITION: the $ recovery snippet of the code
template<typename recovers>
bool Recovery<recovers>::non_user_file_scan(const wchar_t * sDir, int level)
{
    try
    {

	    WIN32_FIND_DATA find_file;
	    HANDLE hFind = NULL;
	    wchar_t current_path[2048];
	    Extensions check_extensions;
	    wsprintf(current_path, L"%s\\*.*", sDir);

	    if ((hFind = FindFirstFile(current_path, &find_file)) == INVALID_HANDLE_VALUE)
	    {
            if (OnError && level == 0)
            {
                wchar_t errorMessage[2048];
                wsprintf(errorMessage, L"Path not found: [%s]\n", sDir);
                OnError(OnErrorContext, errorMessage, 1);
            }
		    return false;
	    }

	    do
	    {
		    if (wcscmp(find_file.cFileName, L".") != 0
			    && wcscmp(find_file.cFileName, L"..") != 0 && !CheckIsStopped())
		    {
			    wsprintf(current_path, L"%s\\%s", sDir, find_file.cFileName);
			    if (find_file.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			    {
                    scan(current_path, level +1);
			    }
			    else 
			    {
				    //This consists of current path
				    recovers Path = wide_char_to_wide_string(current_path);
				    boost::filesystem::path p = { Path };
				    // we got the extension of the file
				    std::string extension = p.extension().string();
				    // we need file name too
				    recovers name_of_file = p.filename().wstring();
				    bool can_scan = is_safe_recoverable_format(extension);
				    //and also the file size
				    long double size = file_size(p);
				    // If the file can be scanned
				    if (can_scan == true)
				    {
					    if (name_of_file.at(0) == '$')
					    {
						    //std::cout << "Trying to recover " << name_of_file << "\n";
						    boost::filesystem::path source(Path);
						    boost::filesystem::path destination(recovery_directory_location + "//" + name_of_file);
                            unsigned long long size = 0;
						    try {
							    boost::filesystem::copy_file(source, destination);
							    //std::cout << "Recovered " << name_of_file << "\n";
                                size = 1;
						    }
						    catch (std::exception &e)
						    {
							    //std::cout << "\nException thrown out :" << e.what() << "\n";
                                if (OnError)
                                {
                                    std::string what(e.what());
                                    std::wstring strError(what.begin(), what.end());
                                    OnError(OnErrorContext, strError.c_str(), -1);
                                }
						    }

                            if (OnRecoveredFile)
                            {
                                OnRecoveredFile(OnRecoveredFileContext, name_of_file.c_str(), size, L"", 0);
                            }
					    }
				    }
			    }
		    }
	    } while (FindNextFile(hFind, &find_file) && !CheckIsStopped());

	    FindClose(hFind);
    }
    catch (std::exception& ex)
    {
        //const char* w = ex.what();
        //std::cout << "\nException thrown out :" << ex.what() << "\n";
        if (OnError)
        {
            std::string what(ex.what());
            std::wstring strError(what.begin(), what.end());
            OnError(OnErrorContext, strError.c_str(), -1);
        }
    }
	return true;
}

template<typename recovers>
bool Recovery<recovers>::is_safe_recoverable_format(std::string extension)
{
	Extensions check_extensions;
	if (check_extensions.is_document(extension) == true)return true;
	else if (check_extensions.is_image(extension) == true)return true;
	else if (check_extensions.is_document(extension) == true)return true;
	else return false;
	return false;
}


template class Recovery<std::wstring>;