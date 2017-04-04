// SWAMI KARUPPASWAMI THUNNAI


#include<iostream>
#include"scanner.h"
#include"Malware.h"
#include"duplicates.h"
#include"recovery.h"
#include"shortcutvirus.h"
#include"gutmann.h"
#include"identity.h"
#include"conversions.h"
#include"password_check.h"
#include"autorun.h"
#include"usb.h"
#include<extras.h>
#include"plugin.h"


int wmain(int argc,wchar_t* argv[])
{
	std::cout << "===================================\n";
	std::cout << "| CyberGod KSGMPRH - DOS ENGINE   |\n";
	std::cout << "| A GPL Licensed Security Toolkit |\n";
	std::cout << "| (C) 2017, VISWESWARAN NAGASIVAM |\n";
	std::cout << "===================================\n";
	int option;
	std::cout << "1.Malware scan\n2.Duplicate Files Remover\n3.Recovery\n4.Secure remove\n5.Remove the shortcut virus\n6.Show Identiity\n7.Password strength checker\n8.Autorun Checker\n9.Scan USB\n10.Quick scan\nChoice : ";
	std::cin >> option;
	std::cin.ignore();
	std::wstring global_location;
	switch (option)
	{
	case 1:
	{
		std::cout << "\nEnter the location :";
		std::getline(std::wcin, global_location);
		system("cls");
		Malware<std::wstring> obj;
		obj.set_boost_scan(false);
		obj.scan(global_location.c_str());
		std::string get_option;
		std::cout << "\n\nScan Scheduled files [y/n]: ";
		std::getline(std::cin,get_option);
		if(get_option=="y")obj.scan_scheduled_files();
		obj.display_suspicious_files();
		process();
		break;
	}
	case 2:
	{
		std::cout << "\nEnter the location :";
		std::getline(std::wcin, global_location);
		Duplicates<std::wstring> obj1;
		obj1.scan(global_location.c_str());
		obj1.find_the_duplicates();
		obj1.get_duplicates();
		process();
		break;
	}
	case 3:
	{
		std::cout << "\nLocation(files will be recovered form this location):\n";
		std::getline(std::wcin, global_location);
		std::wstring recovery_folder;
		std::cout << "\nLocation(recovered filees will be saved here):\n";
		std::getline(std::wcin, recovery_folder);
		Recovery<std::wstring> constructor;
		Recovery<std::wstring> recover(global_location,recovery_folder);
		recover.end();
		process();
		break;
	}
	case 4:
	{
		system("cls");
		std::cout << "WARNING! FILES CANNOT BE RECOVERED BACK ONCE YOU DELETED\n";
		while (true) 
		{
			std::cout << "\nFile to be removed(LOCATION): ";
			std::getline(std::wcin, global_location);
			Gutmann remove;
			// set the pass to 7 thereby making recovering as difficult as possible
			remove.secure_pass(global_location, 7);
			std::cout << "\nFile removed!\n";
		}
		break;
	}
	case 5:
	{
		std::cout << "\nDrive Letter: ";
		std::getline(std::wcin, global_location);
		std::string drive(global_location.begin(), global_location.end());
		ShortCutVirusRemover<std::wstring> rem;
		rem.set_drive_letter(drive);
		if (rem.get_scan_status() == true)
		{
			rem.scan(global_location.c_str());
			rem.remove_all_shotcuts();
			rem.show_suspected_files();
			rem.fix_infection();
			process();
		}
		break;
	}
	case 6:
	{
		Identity<std::wstring> identify;
		identify.display();
		break;
	}
	case 7:
	{
		std::string password;
		std::cout << "Enter the password to check?" << std::endl;
		std::cin >> password;
		PasswordCheck check = password;
		std::cout <<"\ncapitals : " <<check.get_capital_count() << "\n";
		std::cout << "\nlowers : " << check.get_lower_count() << "\n";
		std::cout << "\nnumbers : " << check.get_number_count() << "\n";
		std::cout << "\nsymbols : " << check.get_symbol_count() << "\n";
		std::cout << "\nwhitespaces : " << check.get_whitespace_count() << "\n";
		std::cout << "\nno of guesses needed to crack this password: " << std::to_string(check.return_guess_count()) << "\n";
		break;
	}
	case 8:
	{
		Autorun<std::wstring> autorun;
		std::cout << "\nDrive Letter: ";
		std::getline(std::wcin, global_location);
		std::string drive(global_location.begin(), global_location.end());
		autorun.add_autorun_executables(drive);
		if (autorun.check_autorun_file()) 
		{
			autorun.get_hashes();
			autorun.locate();
			autorun.display();
		}
		else process();
		break;
	}
	case 9:
	{
		std::cout << "\nDrive Letter: ";
		std::getline(std::wcin, global_location);
		std::string drive(global_location.begin(), global_location.end());
		USBScan<std::wstring> usb;
		usb.initialize(drive);
		std::cout << "\nMalicious\n";
		usb.show_malicious_files();
		std::cout << "\nSemi-Malicious\n";
		usb.show_semi_malicious_files();
		std::cout << "\nScanned\n";
		usb.show_files_scanned_in_pc();
		break;
	}
	case 10:
	{
		std::wstring app_data = known_location(FOLDERID_AppsFolder);
		std::wstring program_filesx86 = known_location(FOLDERID_ProgramFilesX86);
		std::wstring windows = known_location(FOLDERID_Windows);
		Malware<std::wstring> obj;
		obj.set_boost_scan(false);
		obj.scan(app_data.c_str());
		obj.scan(program_filesx86.c_str());
		obj.scan(windows.c_str());
		obj.scan_scheduled_files();
		obj.display_suspicious_files();
		break;
	}
	/*case 11:
	{
		Plugin plugin;
		plugin.get_available_plugins();
		plugin.execute_plugin("plugin.py",argc,argv);
		break;
	}*/
	default:
		break;
	}
	int stop;
	std::cin >> stop;
}




