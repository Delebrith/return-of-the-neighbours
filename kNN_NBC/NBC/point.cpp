#include "point.h"


Point::Point(std::vector<double>* attributeValues)
{
	this->attributeValues = attributeValues;
}

std::vector<double>* Point::getAttributeValues()
{
	return this->attributeValues;
}

