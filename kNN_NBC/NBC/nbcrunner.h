#pragma once
#include <vector>
#include <set>
#include "point.h"
#include "CreatedPoint.h"
#include "DatasetPoint.h"
#include "reference_strategy.h"

class NBCRunner 
{
protected:
	// set is sorted using greater operator, thus largest elements will be at the beginning
	typedef std::set<std::pair<double, Point*>, std::greater<std::pair<double, Point*>>> orderedNeighborhood;

	bool tiEnabled;

	int k;
	CreatedPoint referencePoint;
	std::vector<DatasetPoint> points;
	bool enableParallel;

	std::vector<DatasetPoint> initPoints(const std::vector<std::vector<double>>& features);

	std::vector<Point*> getPointsOrderedByDistanceToReference();
	void calculateNeighborhoods();
	void calculateNeighborhoods(std::vector<Point*>& order);
	void calculatePointNeighborhood(int pointId);
	void calculatePointNeighborhood(int pointId, std::vector<Point*>& order);
	virtual void insertPointToNeihborhoodWithDistEqualToLast(orderedNeighborhood&, Point* point, double dist) = 0;
	virtual void insertCloserPointToNeihborhood(orderedNeighborhood&, Point* point, double dist) = 0;
	void calculateReversedNeighbourhoods();
	void calculateNDFs();

	CreatedPoint selectReferencePoint(const std::vector<std::vector<double>>& features,
		const ReferenceStrategy referenceStrategy);
	std::vector<double> getMaxValues(const std::vector<std::vector<double>>& features);
	std::vector<double> getMinValues(const std::vector<std::vector<double>>& features);
	double calculateDistanceToReferencePoint(Point& point);

	void createClusters();
	std::vector<int> getClustering();

public:
	NBCRunner(int k, const ReferenceStrategy referenceStrategy, const std::vector<std::vector<double>>& features, bool enable_parallel);
	std::vector<int> run();
};