#include "kpnn_nbcrunner.h"


void KpNN_NBCRunner::insertCloserPointToNeihborhood(orderedNeighborhood& candidateNeighborhood, Point* point, double dist)
{
	double eps = candidateNeighborhood.begin()->first;

	int points_eq_dist_to_first = 1;
	orderedNeighborhood::iterator it = candidateNeighborhood.begin();
	++it;

	for (; it != candidateNeighborhood.end() && it->first == eps; ++it)
		++points_eq_dist_to_first;
	if (candidateNeighborhood.size() - points_eq_dist_to_first + 1 >= this->k)
		candidateNeighborhood.erase(candidateNeighborhood.begin(), it);

	candidateNeighborhood.insert(std::make_pair(dist, point));
}
