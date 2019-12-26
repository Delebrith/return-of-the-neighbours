#include "nbc.h"
#include "knn_nbcrunner.h"
#include "kpnn_nbcrunner.h"

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

