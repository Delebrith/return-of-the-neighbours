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
	orderedNeighborhood candidateNeighborhood;

	int bw = pointId - 1;
	int fw = pointId + 1;

	//get candidates
	while ((bw >= 0 || fw < this->points.size()) && candidateNeighborhood.size() < this->k)
	{
		if (bw >= 0 && order[bw]->getDistanceFromReference() - order[pointId]->getDistanceFromReference() <
			order[fw]->getDistanceFromReference() - order[pointId]->getDistanceFromReference())
		{
			double dist = order[pointId]->getDistance(*order[bw]);
			candidateNeighborhood.insert(std::make_pair(dist, order[bw]));
			--bw;
		}
		else
		{
			double dist = order[pointId]->getDistance(*order[fw]);
			candidateNeighborhood.insert(std::make_pair(dist, order[fw]));
			++fw;
		}
	}

	//get actual neighborhood
	double eps = candidateNeighborhood.begin()->first;

	while (bw >= 0 && order[bw]->getDistanceFromReference() - order[pointId]->getDistanceFromReference() < eps)
	{
		double dist = order[pointId]->getDistance(*order[bw]);
		if (dist == eps)
			candidateNeighborhood.insert(std::make_pair(dist, order[bw]));
		else if (dist < eps)
		{
			insertCloserPointToNeihborhood(candidateNeighborhood, order[bw], dist);
			eps = candidateNeighborhood.begin()->first;
		}
	}

	while (fw < this->points.size() && order[fw]->getDistanceFromReference() - order[pointId]->getDistanceFromReference() < eps)
	{
		double dist = order[pointId]->getDistance(*order[bw]);
		if (dist == eps)
			candidateNeighborhood.insert(std::make_pair(dist, order[bw]));
		else if (dist < eps)
		{
			insertCloserPointToNeihborhood(candidateNeighborhood, order[bw], dist);
			eps = candidateNeighborhood.begin()->first;
		}
	}

	std::vector<Point*> neighborhood;
	neighborhood.resize(candidateNeighborhood.size());
	for (auto& p : candidateNeighborhood)
		neighborhood.push_back(p.second);

	order[pointId]->setNeihbourhood(std::move(neighborhood));
}

void NBCRunner::calculateReversedNeighbourhoods()
{
	for (DatasetPoint point : this->points) {
		point.updateReversedNeighbourhood();
	}
}

void NBCRunner::calculateNDFs()
{
	for (DatasetPoint point : this->points) {
		point.calculateNDF();
	}
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
