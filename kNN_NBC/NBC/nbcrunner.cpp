#include "nbcrunner.h"
#include <iostream>
#include <math.h>
#include <stack>
#include <algorithm>

NBCRunner::NBCRunner(int k, const ReferenceStrategy referenceStrategy, 
	const std::vector<std::vector<double>>& features, bool enableParallel)
{
	this->k = k;
	this->referencePoint = selectReferencePoint(features, referenceStrategy);
	this->points = initPoints(features);
	this->enableParallel = enableParallel;
}

std::vector<int> NBCRunner::run()
{
	for (Point& p : this->points)
		p.setDistanceFromReference(this->calculateDistanceToReferencePoint(p));

	std::vector<Point*> orderedByDistToReference = this->getPointsOrderedByDistanceToReference();
	this->calculateNeighborhoods(orderedByDistToReference);
	this->calculateReversedNeighbourhoods();
	this->calculateNDFs();
	this->createClusters();

	return this->getClustering();
}

std::vector<DatasetPoint> NBCRunner::initPoints(const std::vector<std::vector<double>>& features) {
	std::vector<DatasetPoint> points;
	points.reserve(features.size());

	for (const std::vector<double>& vect : features) {
		points.push_back(DatasetPoint(&vect));
	}
	return points;
}

static inline bool comparePointsByDistToReference(const Point* a, const Point* b)
{
	return a->getDistanceFromReference() < b->getDistanceFromReference();
}

std::vector<Point*> NBCRunner::getPointsOrderedByDistanceToReference()
{
	std::vector<Point*> ordered;

	ordered.reserve(this->points.size());
	for (Point& p : this->points)
		ordered.push_back(&p);

	std::sort(ordered.begin(), ordered.end(), comparePointsByDistToReference);

	return ordered;
}

void NBCRunner::calculateNeighborhoods(std::vector<Point*>& order)
{
#pragma omp parallel for if(this->enableParallel)
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
		if (bw >= 0 && (fw == this->points.size() || order[pointId]->getDistanceFromReference() - order[bw]->getDistanceFromReference() <
			order[fw]->getDistanceFromReference() - order[pointId]->getDistanceFromReference()))
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

	while (bw >= 0 && order[pointId]->getDistanceFromReference() - order[bw]->getDistanceFromReference() <= eps)
	{
		double dist = order[pointId]->getDistance(*order[bw]);
		if (dist == eps)
			insertPointToNeihborhoodWithDistEqualToLast(candidateNeighborhood, order[bw], dist);
		else if (dist < eps)
		{
			insertCloserPointToNeihborhood(candidateNeighborhood, order[bw], dist);
			eps = candidateNeighborhood.begin()->first;
		}
		--bw;
	}

	while (fw < this->points.size() && order[fw]->getDistanceFromReference() - order[pointId]->getDistanceFromReference() <= eps)
	{
		double dist = order[pointId]->getDistance(*order[fw]);
		if (dist == eps)
			insertPointToNeihborhoodWithDistEqualToLast(candidateNeighborhood, order[fw], dist);
		else if (dist < eps)
		{
			insertCloserPointToNeihborhood(candidateNeighborhood, order[fw], dist);
			eps = candidateNeighborhood.begin()->first;
		}
		++fw;
	}

	std::vector<Point*> neighborhood;
	neighborhood.reserve(candidateNeighborhood.size());
	for (auto& p : candidateNeighborhood)
		neighborhood.push_back(p.second);

	order[pointId]->setNeihbourhood(std::move(neighborhood));
}

void NBCRunner::calculateReversedNeighbourhoods()
{
	for (DatasetPoint& point : this->points) {
		point.updateReversedNeighbourhood();
	}
}

void NBCRunner::calculateNDFs()
{
#pragma omp parallel for if(enableParallel)
	for (int i = 0; i < this->points.size(); ++i) {
		this->points[i].calculateNDF();
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

std::vector<double> NBCRunner::getMaxValues(const std::vector<std::vector<double>>& features)
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

std::vector<double> NBCRunner::getMinValues(const std::vector<std::vector<double>>& features)
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

void NBCRunner::createClusters()
{
	int cluster = 0;

	for (Point& initial : this->points)
	{
		if (initial.getCluster() == -1 && initial.getNDF() >= 1)
		{
			std::stack<Point*> clusterExpansion;
			initial.setCluster(cluster);
			clusterExpansion.push(&initial);

			while (!clusterExpansion.empty())
			{
				Point* current = clusterExpansion.top();
				clusterExpansion.pop();

				for (Point* potentialExpansion : current->getNeigbourhood())
				{
					if (potentialExpansion->getCluster() == -1)
					{
						potentialExpansion->setCluster(cluster);
						
						if (potentialExpansion->getNDF() >= 1)
							clusterExpansion.push(potentialExpansion);
					}
				}
			}

			++cluster;
		}
	}
}

std::vector<int> NBCRunner::getClustering()
{
	std::vector<int> output(this->points.size(), -1);
	
	for (int i = 0; i < this->points.size(); ++i)
		output[i] = this->points[i].getCluster();

	return output;
}
