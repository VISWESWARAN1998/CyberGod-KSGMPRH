// SWAMI KARUPPASWAMI THUNNAI
/*
#define CATCH_CONFIG_MAIN
#include"catch.h"
#include"scanner.h"
#include"Malware.h"
#include"duplicates.h"
#include"extensions.h"
#include"utilities.h"
#include"password_check.h"
#include"autorun.h"

Malware<std::wstring> mal;
Extensions extensions;
Duplicates<std::wstring> dupe;
Scanner scan;
PasswordCheck check = "check123$";
Autorun<std::wstring> autoruns;

TEST_CASE("Testing whether MD5 is obtained properly")
{
	REQUIRE(mal.start_hashing(L"E:\\geckodriver.exe") == "b82a9c22fcf908f472d09103c8e3a335");
	REQUIRE(mal.start_hashing(L"E:\\chromedriver.exe") == "de5f32b9729e277a2f8875cf359e8a5a");
}

TEST_CASE("Testing for the image extensions")
{
	REQUIRE(extensions.is_image(".png") == true);
	REQUIRE(extensions.is_image(".jpg") == true);
	REQUIRE(extensions.is_image(".exe") == false);
	REQUIRE(extensions.is_image("NULL") == false);
}

TEST_CASE("Testing for the common malware extensions")
{
	REQUIRE(extensions.is_common_extension(".png") == false);
	REQUIRE(extensions.is_common_extension(".jpg") == false);
	REQUIRE(extensions.is_common_extension(".exe") == true);
	REQUIRE(extensions.is_common_extension("NULL") == false);
}

TEST_CASE("Testing for the media files")
{
	REQUIRE(extensions.is_media(".mp3") == true);
	REQUIRE(extensions.is_media(".wav") == true);
	REQUIRE(extensions.is_media(".mp4") == true);
	REQUIRE(extensions.is_media("bad") == false);
	REQUIRE(extensions.is_media(".wav") == true);
}

TEST_CASE("Testing for the document extensions")
{
	REQUIRE(extensions.is_document(".mp3") == false);
	REQUIRE(extensions.is_document(".3") == false);
	REQUIRE(extensions.is_document(".docx") == true);
}

TEST_CASE("Testing whether the duplicate file sizes are working")
{
	REQUIRE(dupe.file_size_checker(123, L"C:\\") == false);
	REQUIRE(dupe.file_size_checker(123, L"C:\\") == true);
	REQUIRE(dupe.file_size_checker(123, L"D:\\") == true);
	REQUIRE(dupe.file_size_checker(122, L"D:\\") == false);
}

TEST_CASE("Finalizing the duplicates")
{
	REQUIRE(dupe.check_hash_signatures("aaa", L"aa") == false);
	REQUIRE(dupe.check_hash_signatures("aaa", L"a") == true);
	REQUIRE(dupe.check_hash_signatures("aa", L"aa") == false);
	REQUIRE(dupe.check_hash_signatures("aa", L"a") == true);
	REQUIRE(dupe.check_hash_signatures("jjhjfjhjdff", L"aa") == false);
	REQUIRE(dupe.check_hash_signatures("jhghkkddkjs", L"a") == false);
}


TEST_CASE("Secure file remover test")
{
	REQUIRE(scan.replace_file(L"F:\\dupes\\a.jpg") == true);
}

TEST_CASE("Check the removal process")
{
	REQUIRE(utilityRemove(L"I:\\a.gz") == false);
}

TEST_CASE("Password Strength Analysis")
{
	REQUIRE(check.get_capital_count() == 0);
	REQUIRE(check.get_symbol_count() == 1);
	REQUIRE(check.get_number_count() == 3);
	REQUIRE(check.get_lower_count() == 5);
}

TEST_CASE("Checking the malware in the database in the database")
{
	REQUIRE(mal.check_in_database("781770fda3bd3236d0ab8274577dddde") == true);
	REQUIRE(mal.check_in_database("12c4201fe1db96a1a1711790b52a3cf9") == true);
	REQUIRE(mal.check_in_database("8f80cf878a3e05c06c9d03646443e41d") == true);
	REQUIRE(mal.check_in_database("f58628917abcbcfb2b2258b6b46bf721") == true);
}

TEST_CASE("Adding the files present in the autorun.inf")
{
	REQUIRE(autoruns.add_autorun_executables("I:\\") == true);
	REQUIRE(autoruns.add_autorun_executables("C:\\") == false);
	REQUIRE(autoruns.add_autorun_executables("G:\\") == false);
}



*/