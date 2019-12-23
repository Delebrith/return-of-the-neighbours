#include "point.h"


Point::Point(const std::vector<double>* attributeValues)
{
	this->attributeValues = attributeValues;
}

const std::vector<double>* Point::getAttributeValues()
{
	return this->attributeValues;
}

const std::vector<Point*>& Point::getNeigbourhood() const
{
	return this->neighbourhood;
}

void Point::setNeihbourhood(std::vector<Point*>&& nb)
{
	this->neighbourhood = std::vector<Point*>(nb);
}

double Point::getDistanceFromReference() const
{
	return this->distanceFromReference;
}

double Point::getDistance(const Point& p) const
{
	double dist = 0.;
	for (int i = 0; i < p.attributeValues->size() && this->attributeValues->size(); ++i)
	{
		double diff = (p.attributeValues - this->attributeValues);
		dist += diff * diff;
	}

	return dist;
}
