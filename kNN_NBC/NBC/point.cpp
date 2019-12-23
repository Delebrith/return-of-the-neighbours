#include "point.h"


Point::Point()
{
}

Point::Point(const std::vector<double>* attributeValues)
{
	this->attributeValues = attributeValues;
}

const std::vector<double>* Point::getAttributeValues()
{
	return this->attributeValues;
}

