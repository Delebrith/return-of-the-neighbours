#pragma once
#include <vector>
#include <set>
#include "point.h"

class NBCRunner 
{
protected:
	int k;
	std::vector<Point> points;
	std::vector<Point> initPoints(const std::vector<std::vector<double>>& features);

	
	// set is sorted using greater operator, thus largest elements will be at the beginning
	typedef std::set<std::pair<double, Point*>, std::greater<std::pair<double, Point*>>> orderedNeighborhood;

	void calculateNeighborhoods(std::vector<Point*>& order);
	void calculatePointNeighborhood(int pointId, std::vector<Point*>& order);
	virtual void insertCloserPointToNeihborhood(orderedNeighborhood&, Point* point, double dist) = 0;
public:
	NBCRunner(const std::vector<std::vector<double>>& features, int k);
	std::vector<int> run();
};