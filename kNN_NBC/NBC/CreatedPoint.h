#pragma once
#include "point.h"

class CreatedPoint :
	public Point
{
	const std::vector<double> attributeValues;
public:
	CreatedPoint() {};
	CreatedPoint(const std::vector<double> attributeValues) : attributeValues(attributeValues) {};
	const std::vector<double>* getAttributeValues();
};

