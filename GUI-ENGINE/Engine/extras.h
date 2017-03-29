#pragma once
// SWAMI KARUPPASWAMI THUNNAI
#include<iostream>
#include<Windows.h>
#include <KnownFolders.h>
#include <ShlObj.h>
#ifndef INDLL_H
#define INDLL_H

#ifdef EXPORTING_DLL
extern __declspec(dllexport) double x_screen_size();
#else
extern __declspec(dllimport) double x_screen_size();
#endif

#ifdef EXPORTING_DLL
extern __declspec(dllexport) double y_screen_size();
#else
extern __declspec(dllimport) double y_screen_size();
#endif


#ifdef EXPORTING_DLL
extern __declspec(dllexport) std::wstring known_location(const GUID knownlocation);
#else
extern __declspec(dllimport) std::wstring known_location(const GUID knownlocation);
#endif


#endif