#pragma once
#include "point.h"

class DatasetPoint :
	public Point
{
	const std::vector<double>* attributeValues;
public:
	DatasetPoint(const std::vector<double>* attributeValues) : attributeValues(attributeValues) {};
	const std::vector<double>* getAttributeValues() const;
};

