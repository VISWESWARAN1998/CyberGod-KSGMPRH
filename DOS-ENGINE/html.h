// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<string>


// This class may be useful only to the DOS Engine.
// This calss is used to create generate the HTML file for our dos engine.
// It is unworthy to add create tags and concat it to the string everywhere and it will
// spoil the code so I created a seperate class for this.
class HTML
{
private:
	std::wstring location;
public:
	bool create_file(std::wstring location,std::string title);
	void initialize_headers();
	void initialize_message(std::string tag,std::string class_);
	void finalize_message(std::string message);
	bool document(std::wstring tag, std::wstring content);
	bool finalize_html();
};
