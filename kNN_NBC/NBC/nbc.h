#pragma once
#include <vector>

#ifdef _EXPORTING_NBC
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

int DLL_EXPORT fun(int x);
std::vector<int> DLL_EXPORT fun_negate(std::vector<int> arg);
