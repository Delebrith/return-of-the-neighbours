#pragma once
#include <vector>
#include "point.h"

class NBCRunner 
{
protected:
	std::vector<Point> points;
	std::vector<Point> initPoints(std::vector<std::vector<double>>* features);
public:
	NBCRunner(std::vector<std::vector<double>>* features);
	std::vector<int> run();
};