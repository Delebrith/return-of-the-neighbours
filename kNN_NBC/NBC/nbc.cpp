#include "nbc.h"
#include "knn_nbcrunner.h"
#include "kpnn_nbcrunner.h"

std::vector<int> a = std::vector<int>(1000000);

int fun(int x)
{
	//check multithreadin lib
	#pragma omp parallel for
	for (int i = 0; i < a.size(); ++i)
		for (int j = 0; j < 10000; ++j)
			a[i] = i;

	return a[8000] - a[7999]; // should be equal to 1
}

std::vector<int> fun_negate(std::vector<int> arg)
{
	std::vector<int> out;
	for (int a : arg)
		out.push_back(-a);
	return out;
}

std::vector<int> nbc_kNN(int k, const ReferenceStrategy referenceStategy,
	const std::vector<std::vector<double>> & attributes)
{
	KNN_NBCRunner nbcRunner(k, referenceStategy, attributes);
	return nbcRunner.run();
}

std::vector<int> nbc_kpNN(int k, const ReferenceStrategy referenceStategy,
	const std::vector<std::vector<double>>& attributes)
{
	KpNN_NBCRunner nbcRunner(k, referenceStategy, attributes);
	return nbcRunner.run();
}

