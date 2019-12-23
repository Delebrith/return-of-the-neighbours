#include "nbcrunner.h"

NBCRunner::NBCRunner(std::vector<std::vector<double>>* features)
{
	this->points = this->initPoints(features);
}

std::vector<int> NBCRunner::run()
{
	return std::vector<int>();
}

std::vector<Point> NBCRunner::initPoints(std::vector<std::vector<double>>* features) {
	std::vector<Point> points;
	for (std::vector<double> vect : *(features)) {
		points.push_back(Point(&vect));
	}
	return points;
}
