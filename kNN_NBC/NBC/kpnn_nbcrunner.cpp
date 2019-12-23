#include "kpnn_nbcrunner.h"


void KpNN_NBCRunner::insertCloserPointToNeihborhood(orderedNeighborhood& nb, Point* point, double dist)
{
	double eps = nb.begin()->first;

	int num_eq_to_first = 1;
	orderedNeighborhood::iterator it = nb.begin();
	++it;

	for (; it != nb.end() && it->first == eps; ++it)
		++num_eq_to_first;
	if (nb.size() - num_eq_to_first + 1 >= this->k)
		nb.erase(nb.begin(), it);

	nb.insert(std::make_pair(dist, point));
}
