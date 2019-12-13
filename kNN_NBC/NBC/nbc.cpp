#include "nbc.h"


int a[1000000];

int fun(int x)
{
	//check multithreadin lib
	#pragma omp parallel for
	for (int i = 0; i < 1000000; ++i)
		for (int j = 0; j < 10000; ++j)
			a[i] = i;

	return a[8000] - a[7999]; // should be equal to 1
}
