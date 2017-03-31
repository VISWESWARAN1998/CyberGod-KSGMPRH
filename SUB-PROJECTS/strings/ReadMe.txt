Strings:
==========

This project is inspired by the famous strings application https://technet.microsoft.com/en-us/sysinternals/strings.aspx 
This source can be built into .dll and can be used to extract ascii strings from the executable.
The project has sqlite dependency which can be easily removed and could be suited well for your project.


Removing sqlite depenency:
============================

Use only strings.h and strings.cpp file. By adding this single header and source file you could give your application the facility to extract ascii strings from the binary file.