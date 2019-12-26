#pragma once
#include<vector>

class Point
{
	std::vector<Point*> neighbourhood;
	double distanceFromReference = 0;
	int reverseNeighbourhoodCounter = 0;
	double ndf;

	int cluster = -1;
public:
	Point() {};

	virtual const std::vector<double>* getAttributeValues() const = 0;
	const std::vector<Point*>& getNeigbourhood() const;
	void setNeihbourhood(std::vector<Point*>&&);
	void updateReversedNeighbourhood();
	void calculateNDF();
	
	//returns a square of cartesian distance
	double getDistance(const Point& p) const;
	void setDistanceFromReference(double distance);
	double getDistanceFromReference() const;
	int& getReverseNeighbourhoodCounter();
	double getNDF();

	int getCluster() const;
	void setCluster(int cluster);
};