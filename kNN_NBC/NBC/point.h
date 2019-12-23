#include<vector>

class Point 
{
	const std::vector<double>* attributeValues;
public:
	Point();
	Point(const std::vector<double>* attributeValues);
	
	const std::vector<double>* getAttributeValues();
};