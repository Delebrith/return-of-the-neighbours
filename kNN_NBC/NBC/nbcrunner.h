#pragma once
#include <vector>
#include "point.h"
#include "CreatedPoint.h"
#include "reference_strategy.h"

class NBCRunner 
{
protected:
	int k;
	CreatedPoint referencePoint;
	std::vector<Point> points;

	std::vector<Point> initPoints(const std::vector<std::vector<double>>& features);
	CreatedPoint selectReferencePoint(const std::vector<std::vector<double>>& features,
		const ReferenceStrategy referenceStrategy);
	std::vector<double>& getMaxValues(const std::vector<std::vector<double>>& features);
	std::vector<double>& getMinValues(const std::vector<std::vector<double>>& features);

public:
	NBCRunner(const int k, const ReferenceStrategy referenceStrategy, const const std::vector<std::vector<double>>& features);
	std::vector<int> run();
};