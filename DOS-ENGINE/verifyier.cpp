// SWAMI KARUPPASWAMI THUNNAI
#include "verifyier.h"
#include"utilities.h"
#include<Windows.h>
using namespace sqlite;

// This constructor will take the ID as an argument
// which will be hard-coded usually and gets the hash and size of the file
// which is present in the respective ID.
Verifyier::Verifyier(int ID)
{
	id = ID;
	//std::cout << "Verifying the files for the ID "<<ID<<"\n";
	try {
		database db("verifyier//verifyier.db");
		db << "select ID,Hash,Size from hashes where ID = ? ;" 
			<< ID 
			>> [&](std::unique_ptr<int> id, std::string hash, int size) 
		{
			if (id != nullptr)
			{
				hash_of_file = hash;
				size_of_file = size;
			}
			else std::cout << "Something went wrong with the database\n";
		};
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
	}
	
}

void Verifyier::can_process_further()
{
	// If the hash of the file is computed then this conditional statement will be executed
	if (hash_of_file.size() == 32)
	{
		switch (id)
		{
		case 0:
		{
			std::string md5 = calculate_md5(L"Adder.py");
			if (md5 != hash_of_file)
			{
				int message = MessageBox(NULL, L"Adder.py has been modified! Have you modified it?", L"File Modification found", MB_YESNO|MB_ICONWARNING);
				if (message == IDYES)
				{
					int size = boost::filesystem::file_size("Adder.py");
					if (update_hashes_and_size(0, md5, size) == true)
					{
						MessageBox(NULL, L"The details have been updated!", L"Successes", MB_OK | MB_ICONASTERISK);
					}
				}
				else handle_invalid_id();
			}
			break;
		}
		case 1:
		{
			std::string md5 = calculate_md5(L"Hunter.py");
			if (md5 != hash_of_file)
			{
				int message = MessageBox(NULL, L"Hunter.py has been modified! Have you modified it?", L"File Modification found", MB_YESNO | MB_ICONWARNING);
				if (message == IDYES)
				{
					int size = boost::filesystem::file_size("Hunter.py");
					if (update_hashes_and_size(1, md5, size) == true)
					{
						MessageBox(NULL, L"The details have been updated!", L"Successes", MB_OK | MB_ICONASTERISK);
					}
				}
				else handle_invalid_id();
			}
			break;
		}
		case 2:
		{
			std::string md5 = calculate_md5(L"process_hunter.py");
			if (md5 != hash_of_file)
			{
				int message = MessageBox(NULL, L"process_hunter.py has been modified! Have you modified it?", L"File Modification found", MB_YESNO | MB_ICONWARNING);
				if (message == IDYES)
				{
					int size = boost::filesystem::file_size("process_hunter.py");
					if (update_hashes_and_size(2, md5, size) == true)
					{
						MessageBox(NULL, L"The details have been updated!", L"Successes", MB_OK | MB_ICONASTERISK);
					}
				}
				else handle_invalid_id();
			}
			break;
		}
		default:
			handle_invalid_id();
			break;
		}
	}
	else handle_invalid_id();
}

void Verifyier::handle_invalid_id()
{
	std::cout << "The ID might be invaid!\nKindly download the binaries from the github link";
	ShellExecute(NULL, 0, L"https://github.com/VISWESWARAN1998/CyberGod-KSGMPRH/releases", 0, 0, SW_SHOWMAXIMIZED);
}

bool Verifyier::update_hashes_and_size(int id,std::string hash, int size)
{
	try
	{
		database db("verifyier//verifyier.db");
		db << "update hashes set Hash = ? where id = ? ;" << hash << id;
		db << "update hashes set Size = ? where id= ?" << size << id;
		return true;
	}
	catch (std::exception &e)
	{
		return false;
	}
	return false;
}




// Bootloader -> This method will be executed when the program is initially executed
void boot_loader()
{
	Verifyier verify(0);
	verify.can_process_further();
	Verifyier verify1(1);
	verify1.can_process_further();
	Verifyier verify2(2);
	verify2.can_process_further();
}