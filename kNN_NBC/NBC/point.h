#include<vector>

class Point 
{
	std::vector<double>* attributeValues;
public:
	Point(std::vector<double>* attributeValues);
	
	std::vector<double>* getAttributeValues();
};