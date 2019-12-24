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

std::vector<DatasetPoint> NBCRunner::initPoints(const std::vector<std::vector<double>>& features) {
	std::vector<DatasetPoint> points;
	points.reserve(features.size());

	for (const std::vector<double>& vect : features) {
		points.push_back(DatasetPoint(&vect));
	}
	return points;
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

