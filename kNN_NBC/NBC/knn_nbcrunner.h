#pragma once
#include "nbcrunner.h"

class KNN_NBCRunner : public NBCRunner
{
public:
	KNN_NBCRunner(const std::vector<std::vector<double>>& features, int k) : NBCRunner(features, k) {}
protected:
	virtual void insertCloserPointToNeihborhood(orderedNeighborhood&, Point* point, double dist);
};
