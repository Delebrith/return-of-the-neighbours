#include "CreatedPoint.h"
const std::vector<double>* CreatedPoint::getAttributeValues() const
{
	return &(this->attributeValues);
}