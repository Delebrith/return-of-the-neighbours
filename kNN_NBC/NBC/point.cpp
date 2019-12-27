#include "point.h"
#include <math.h>


const std::vector<Point*>& Point::getNeigbourhood() const
{
	return this->neighbourhood;
}

void Point::setNeihbourhood(std::vector<Point*>&& nb)
{
	this->neighbourhood = std::vector<Point*>(nb);
}

void Point::updateReversedNeighbourhood()
{
	for (Point* point : this->neighbourhood) {
		point->getReverseNeighbourhoodCounter()++;
	}
}

void Point::calculateNDF()
{
	this->ndf = this->reverseNeighbourhoodCounter / (double) this->neighbourhood.size();
}

int& Point::getReverseNeighbourhoodCounter()
{
	return this->reverseNeighbourhoodCounter;
}

double Point::getNDF()
{
	return this->ndf;
}

void Point::setDistanceFromReference(double distance)
{
	this->distanceFromReference = distance;
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
		double diff = ((*p.getAttributeValues())[i] - (*this->getAttributeValues())[i]);
		dist += diff * diff;
	}

	return sqrt(dist);
}

int Point::getCluster() const
{
	return this->cluster;
}

void Point::setCluster(int cluster)
{
	this->cluster = cluster;
}
