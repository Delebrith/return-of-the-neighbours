#pragma once
#include <vector>
#include "reference_strategy.h"

#ifdef _EXPORTING_NBC
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

int DLL_EXPORT fun(int x);
std::vector<int> DLL_EXPORT fun_negate(std::vector<int> arg);

std::vector<int> DLL_EXPORT nbc_kNN(const int k, const ReferenceStrategy referenceStategy,
	const std::vector<std::vector<double>>& attributes);

std::vector<int> DLL_EXPORT nbc_kpNN(const int k, const ReferenceStrategy referenceStategy,
	const std::vector<std::vector<double>>& attributes);
