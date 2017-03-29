// SWAMI KARUPPASWAMI THUNNAI

#include<iostream>
#include<wx\volume.h>
#include "identity.h"

// Added Unicode support and tested!

// We need a GUI dev to add this into a list box which is neat and clean!


template<typename T>
void Identity<T>::display()
{
	std::cout <<"\nOperating System: "<< os_info<<"\n";
	std::cout << "\nOS version: " << os_version << "\n";
	std::cout << "\nHome Directory: " << home_dir << "\n";
	std::cout << "\nUser Name: " << user_name << "\n";
	std::cout << "\n64-bit Processor: " <<is_64Bit << "\n";
	std::cout << "\nHost Name: " << host << "\n";
	std::cout << "\nRam size: " << ramSize << "GB\n";
	wxArrayString volume = wxFSVolume::GetVolumes();
	int no_of_volumes = volume.size();
	for (int i = 0; i < no_of_volumes; i++)
	{
		std::string drive = std::string(volume[i].c_str());
		if (get_drive_status(drive) == 0)std::cout <<"\n"<<drive<<" : "<< "Dirve Unknown";
		if (get_drive_status(drive) == 1)std::cout << "\n" << drive << " : " << "Dirve No Root Directory";
		if (get_drive_status(drive) == 2)std::cout << "\n" << drive << " : " << "Removable Media Drive";
		if (get_drive_status(drive) == 3)std::cout << "\n" << drive << " : " << "Fixed drive";
		if (get_drive_status(drive) == 4)std::cout << "\n" << drive << " : " << "Remote drives";
		if (get_drive_status(drive) == 5)std::cout << "\n" << drive << " : " << "CD Drive";
		if (get_drive_status(drive) == 6)std::cout << "\n" << drive << " : " << "RAM DISK";
	}
}


// Added the template support
template class Identity<std::wstring>;