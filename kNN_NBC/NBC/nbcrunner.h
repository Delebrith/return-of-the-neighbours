#pragma once
#include <vector>
#include "point.h"
#include "CreatedPoint.h"
#include "DatasetPoint.h"
#include "reference_strategy.h"

class NBCRunner 
{
protected:
	int k;
	CreatedPoint referencePoint;
	std::vector<DatasetPoint> points;

	std::vector<DatasetPoint> initPoints(const std::vector<std::vector<double>>& features);
	CreatedPoint selectReferencePoint(const std::vector<std::vector<double>>& features,
		const ReferenceStrategy referenceStrategy);
	std::vector<double>& getMaxValues(const std::vector<std::vector<double>>& features);
	std::vector<double>& getMinValues(const std::vector<std::vector<double>>& features);
	double calculateDistance(Point& point1, Point& point2);
	double calculateDistanceToReferencePoint(Point& point);

public:
	NBCRunner(const int k, const ReferenceStrategy referenceStrategy, const std::vector<std::vector<double>>& features);
	std::vector<int> run();
};