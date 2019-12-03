#pragma once

#ifdef _EXPORTING_NBC
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT __declspec(dllimport)
#endif

int DLL_EXPORT fun(int x);
