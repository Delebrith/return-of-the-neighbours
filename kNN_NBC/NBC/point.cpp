#include "point.h"


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
	for (int i = 0; i < p.getAttributeValues()->size() && this->getAttributeValues()->size(); ++i)
	{
		double diff = (p.getAttributeValues() - this->getAttributeValues());
		dist += diff * diff;
	}

	return dist;
}
