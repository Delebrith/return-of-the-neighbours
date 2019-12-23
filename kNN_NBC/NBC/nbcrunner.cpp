#include "nbcrunner.h"

NBCRunner::NBCRunner(const std::vector<std::vector<double>>& features, int k)
{
	this->points = initPoints(features);
	this->k = k;
}

std::vector<int> NBCRunner::run()
{
	return std::vector<int>();
}

std::vector<Point> NBCRunner::initPoints(const std::vector<std::vector<double>>& features) {
	std::vector<Point> points;
	points.reserve(features.size());

	for (const std::vector<double>& vect : features) {
		points.push_back(Point(&vect));
	}
	return points;
}

void NBCRunner::calculateNeighborhoods(std::vector<Point*>& order)
{
	for (int i = 0; i < this->points.size(); ++i)
		this->calculatePointNeighborhood(i, order);
}

void NBCRunner::calculatePointNeighborhood(int pointId, std::vector<Point*>& order)
{
	orderedNeighborhood nb;

	int bw = pointId - 1;
	int fw = pointId + 1;

	//get candidates
	while ((bw >= 0 || fw < this->points.size()) && nb.size() < this->k)
	{
		if (bw >= 0 && order[bw]->getDistanceFromReference() - order[pointId]->getDistanceFromReference() <
			order[fw]->getDistanceFromReference() - order[pointId]->getDistanceFromReference())
		{
			double dist = order[pointId]->getDistance(*order[bw]);
			nb.insert(std::make_pair(dist, order[bw]));
			--bw;
		}
		else
		{
			double dist = order[pointId]->getDistance(*order[fw]);
			nb.insert(std::make_pair(dist, order[fw]));
			++fw;
		}
	}

	//get actual neighborhood
	double eps = nb.begin()->first;

	while (bw >= 0 && order[bw]->getDistanceFromReference() - order[pointId]->getDistanceFromReference() < eps)
	{
		double dist = order[pointId]->getDistance(*order[bw]);
		if (dist == eps)
			nb.insert(std::make_pair(dist, order[bw]));
		else if (dist < eps)
		{
			insertCloserPointToNeihborhood(nb, order[bw], dist);
			eps = nb.begin()->first;
		}
	}

	while (fw < this->points.size() && order[fw]->getDistanceFromReference() - order[pointId]->getDistanceFromReference() < eps)
	{
		double dist = order[pointId]->getDistance(*order[bw]);
		if (dist == eps)
			nb.insert(std::make_pair(dist, order[bw]));
		else if (dist < eps)
		{
			insertCloserPointToNeihborhood(nb, order[bw], dist);
			eps = nb.begin()->first;
		}
	}

	std::vector<Point*> neighborhood;
	neighborhood.resize(nb.size());
	for (auto& p : nb)
		neighborhood.push_back(p.second);

	order[pointId]->setNeihbourhood(std::move(neighborhood));
}
