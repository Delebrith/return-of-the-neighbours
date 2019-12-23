#include "nbcrunner.h"
#include <iostream>

NBCRunner::NBCRunner(const int k, const ReferenceStrategy referenceStrategy, 
	const std::vector<std::vector<double>>& features) 
{
	this->k = k;
	this->referencePoint = selectReferencePoint(features, referenceStrategy);
	this->points = initPoints(features);
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

Point NBCRunner::selectReferencePoint(const std::vector<std::vector<double>>& features, const ReferenceStrategy strategy)
{
	if (strategy == ReferenceStrategy::MAX_VALUE)
	{
		return Point(&getMaxValues(features));
	}
	else
	{
		return Point(&getMinValues(features));
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

