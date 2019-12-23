#pragma once
#include "nbcrunner.h"

class KpNN_NBCRunner : public NBCRunner
{
public:
	KpNN_NBCRunner(const std::vector<std::vector<double>>& features, int k) : NBCRunner(features, k) {}
protected:
	virtual void insertCloserPointToNeihborhood(orderedNeighborhood&, Point* point, double dist);
};
