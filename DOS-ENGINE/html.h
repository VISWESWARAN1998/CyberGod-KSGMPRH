// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<string>

/*
This is the newest feature and will improve later in DOS engine
*/
class HTML
{
private:
	std::wstring location;
public:
	bool create_file(std::wstring location,std::string title,std::string style_sheet);
	bool document(std::wstring tag, std::wstring content);
	bool finalize_html();
};
