// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<string>
class HTML
{
private:
	std::wstring location;
public:
	bool create_file(std::wstring location,std::string title,std::string style_sheet);
	bool document(std::wstring tag, std::wstring content);
	bool finalize_html();
};
