#include<vector>

class Point
{
	const std::vector<double>* attributeValues;
	std::vector<Point*> neighbourhood;
	double distanceFromReference = 0;
public:
	Point(const std::vector<double>* attributeValues);
	
	const std::vector<double>* getAttributeValues();
	const std::vector<Point*>& getNeigbourhood() const;
	void setNeihbourhood(std::vector<Point*>&&);
	
	//returns a square of cartesian distance
	double getDistance(const Point& p) const;
	double getDistanceFromReference() const;
};