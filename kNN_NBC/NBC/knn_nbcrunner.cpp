#include "knn_nbcrunner.h"


void KNN_NBCRunner::insertCloserPointToNeihborhood(orderedNeighborhood& nb, Point* point, double dist)
{
	nb.erase(nb.begin());
	nb.insert(std::make_pair(dist, point));
}
