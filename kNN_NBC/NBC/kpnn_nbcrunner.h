#pragma once
#include "nbcrunner.h"

class KpNN_NBCRunner : public NBCRunner
{
public:
	KpNN_NBCRunner(int k, ReferenceStrategy strategy,
		const std::vector<std::vector<double>>& features,
		bool enableParallel) : NBCRunner(k, strategy, features, enableParallel) {}
protected:
	virtual void insertPointToNeihborhoodWithDistEqualToLast(orderedNeighborhood&, Point* point, double dist);
	virtual void insertCloserPointToNeihborhood(orderedNeighborhood&, Point* point, double dist);
};
