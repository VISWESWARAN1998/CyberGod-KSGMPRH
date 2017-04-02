// SWAMI KARUPPASWAMI THUNNAI

#include "html.h"
#include<fstream>

// This method will initialize the HTML5 document
// This method should not be present inside the looping statement
bool HTML::create_file(std::wstring location,std::string title)
{
	this->location = location;
	std::ofstream file;
	file.open(location);
	if (file.is_open())
	{
		file << "<!DOCTYPE HTML>" << "\n";
		file << "<html>" << "\n";
		file << "<head>" << "\n";
		file << "<title>" << title << "</title>" << "\n";
		file.close();
		return true;
	}
	return false;
}

// This method will initialize the HTML5 document
// This method should not be present inside the looping statement
// You may use this method to add any special tags like style and script in your head tag
void HTML::initialize_headers()
{
	std::ofstream file;
	file.open(location, std::ios::app);
	if (file.is_open())
	{
		file << "<style>table, th, td {border: 2px solid black;}</style>";
		file << "\n";
		// close the head tag and open the body tag
		file << "</head><body>\n";
		file.close();
	}
}

// used for adding tags like this <a class="classx">
void HTML::initialize_message(std::string tag, std::string class_)
{
	std::ofstream file;
	file.open(location,std::ios::app);
	if (file.is_open())
	{
		if (class_=="NULL")file << "<" << tag <<">";
		else file << "<" << tag << " class=" << class_ << ">"; 
		file.close();
	}
}

void HTML::finalize_message(std::string message)
{
	std::ofstream file;
	file.open(location,std::ios::app);
	if (file.is_open())
	{
		file << "</message" << ">";
		file.close();
	}
}

// This is the method which is actually used to document the html file
bool HTML::document(std::wstring tag, std::wstring content)
{
	std::ofstream html;
	std::string TAG(tag.begin(), tag.end());
	std::string CONTENT(content.begin(), content.end());
	html.open(location, std::ios::app);
	if (html.is_open())
	{
		html << "<" << TAG << ">" << CONTENT << "</" << TAG << ">\n";
		html.close();
		return true;
	}
	return false;
}

// This method will finalize the html document .
// Tt should not be present inside the looping statement.
bool HTML::finalize_html()
{
	std::ofstream html;
	html.open(location,std::ios::app);
	if (html.is_open())
	{
		html << "</body>\n</html>";
		html.close();
		return true;
	}
	return false;
}
