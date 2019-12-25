#include "knn_nbcrunner.h"


void KNN_NBCRunner::insertCloserPointToNeihborhood(orderedNeighborhood& candidateNeighborhood, Point* point, double dist)
{
	candidateNeighborhood.erase(candidateNeighborhood.begin());
	candidateNeighborhood.insert(std::make_pair(dist, point));
}
