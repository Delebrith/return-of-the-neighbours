#pragma once
#include<vector>

class Point 
{
public:
	Point() {};
	virtual const std::vector<double>* getAttributeValues() = 0;
};