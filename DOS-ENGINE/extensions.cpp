// SWAMI KARUPPASWAMI THUNNAI
#include<Windows.h>
#include "extensions.h"

Extensions::Extensions()
{
	int i = 0;
	// common image formats
	std::string image_formats[] = { ".jpg",".jpeg",".png",".bmp",".gif",".ppm",".pgm",".pnm",".pbm","NULL" };
	while (image_formats[i] != "NULL")
	{
		image_extensions.insert(image_formats[i]);
		i++;
	}
	i = 0;
	// Most necessarily used for boost scan
	std::string common_malware_formats[] = { ".exe",".dll",".pdf",".doc",".xls",".xlxs",".vbs",".ppt","NULL"};
	while (common_malware_formats[i] != "NULL")
	{
		common_malware_extensions.insert(common_malware_formats[i]);
		i++;
	}
	i = 0;
	// Audio and Video formats supported
	std::string media_formats[] = { ".3gp",".mp3",".mp4",".wav",".aiff",".m4a",".m4b",".m4p",".wma",".webm",".flv",".avi","NULL" };
	while (media_formats[i] != "NULL")
	{
		media_extensions.insert(media_formats[i]);
		i++;
	}
	i = 0;
	// Document formats
	std::string document_formats[] = { ".doc",".docx",".txt",".rtf",".xps",".xls",".xlxs",".ppt",".ppts",".pdf",".epub","NULL" };
	while (document_formats[i]!="NULL")
	{
		document_extensions.insert(document_formats[i]);
		i++;
	}
	i = 0;

}

// Need to find whether the file is an image or not
const bool Extensions::is_image(std::string extension)
{
	std::set<std::string>::iterator itr = image_extensions.find(extension);
	if (itr != image_extensions.end())return true;
	return false;
}

const bool Extensions::is_common_extension(std::string extension)
{
	std::set<std::string>::iterator itr = common_malware_extensions.find(extension);
	if (itr != common_malware_extensions.end())return true;
	return false;
}

const bool Extensions::is_media(std::string extension)
{
	std::set<std::string>::iterator itr = media_extensions.find(extension);
	if (itr != media_extensions.end())return true;
	return false;
}

const bool Extensions::is_document(std::string extension)
{
	std::set<std::string>::iterator itr = document_extensions.find(extension);
	if (itr != document_extensions.end())return true;
	return false;
}

const bool Extensions::is_shortcut(std::string extension)
{
	if (extension == shortcut)return true;
	return false;
}


