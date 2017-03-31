// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include<string>
#ifndef INDLL_H
#define INDLL_H

#ifndef EXPORTING_DLL
extern __declspec(dllexport) void init();
extern __declspec(dllexport) bool is_string_present(int choice, std::wstring location);
#else
extern __declspec(dllimport) void init();
extern __declspec(dllimport) bool is_string_present(int choice, std::wstring location);
#endif 
#endif

bool is_string_present(int choice, std::wstring location);
void init();