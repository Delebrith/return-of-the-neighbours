#pragma once
#include "nbcrunner.h"

class KNN_NBCRunner : public NBCRunner
{
public:
	KNN_NBCRunner(int k, ReferenceStrategy strategy,
		const std::vector<std::vector<double>>& features,
		bool enableParallel) : NBCRunner(k, strategy, features, enableParallel) {}
protected:
	virtual void insertPointToNeihborhoodWithDistEqualToLast(orderedNeighborhood&, Point* point, double dist);
	virtual void insertCloserPointToNeihborhood(orderedNeighborhood&, Point* point, double dist);
};
