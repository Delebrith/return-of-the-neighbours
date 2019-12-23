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
