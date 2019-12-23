#pragma once
#include <vector>
#include "point.h"

class NBCRunner 
{
protected:
	std::vector<Point> points;
	std::vector<Point> initPoints(const std::vector<std::vector<double>>& features);
public:
	NBCRunner(const std::vector<std::vector<double>>& features);
	std::vector<int> run();
};