// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<iostream>
#include<string>
#include<set>

class Extensions
{
private:
	std::string shortcut = ".lnk";
	std::set<std::string> image_extensions;
	std::set<std::string> common_malware_extensions;
	std::set<std::string> media_extensions;
	std::set<std::string> document_extensions;
public:
	Extensions();
	const bool is_image(std::string extension);
	const bool is_common_extension(std::string extension);
	const bool is_media(std::string extension);
	const bool is_document(std::string extension);
	const bool is_shortcut(std::string extension);
};