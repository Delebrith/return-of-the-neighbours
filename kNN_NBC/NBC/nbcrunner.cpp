#include "nbcrunner.h"
#include <iostream>
#include <math.h>

NBCRunner::NBCRunner(int k, const ReferenceStrategy referenceStrategy, 
	const std::vector<std::vector<double>>& features) 
{
	this->k = k;
	this->referencePoint = selectReferencePoint(features, referenceStrategy);
	this->points = initPoints(features);
	this->k = k;
}

std::vector<int> NBCRunner::run()
{
	return std::vector<int>();
}

std::vector<DatasetPoint> NBCRunner::initPoints(const std::vector<std::vector<double>>& features) {
	std::vector<DatasetPoint> points;
	points.reserve(features.size());

	for (const std::vector<double>& vect : features) {
		points.push_back(DatasetPoint(&vect));
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

CreatedPoint NBCRunner::selectReferencePoint(const std::vector<std::vector<double>>& features, const ReferenceStrategy strategy)
{
	if (strategy == ReferenceStrategy::MAX_VALUE)
	{
		return CreatedPoint(getMaxValues(features));
	}
	else
	{
		return CreatedPoint(getMinValues(features));
	}
}

std::vector<double>& NBCRunner::getMaxValues(const std::vector<std::vector<double>>& features)
{
	std::vector<double> extremeValues;
	int numberOfFeatures = features.front().size();
	for (int i = 0; i < numberOfFeatures; i++)
	{
		double maxValue = features.front().at(0);
		for (int j = 0; j < features.size(); j++)
		{
			if (maxValue < features.at(j).at(i))
			{
				maxValue = features.at(j).at(i);
			}
		}
		extremeValues.push_back(maxValue);
	}
	return extremeValues;
}

std::vector<double>& NBCRunner::getMinValues(const std::vector<std::vector<double>>& features)
{
	std::vector<double> extremeValues;
	int numberOfFeatures = features.front().size();
	for (int i = 0; i < numberOfFeatures; i++)
	{
		double minValue = features.front().at(0);
		for (int j = 0; j < features.size(); j++)
		{
			if (minValue > features.at(j).at(i))
			{
				minValue = features.at(j).at(i);
			}
		}
		extremeValues.push_back(minValue);
	}
	return extremeValues;
}

double NBCRunner::calculateDistanceToReferencePoint(Point& point)
{
	return this->referencePoint.getDistance(point);
}
