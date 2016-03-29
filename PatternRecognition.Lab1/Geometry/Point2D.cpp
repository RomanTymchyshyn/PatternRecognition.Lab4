#include "Point2D.h"

#include "GeometryUtilities.h"

Point2D Point2D::Rotate(const double & angle) const
{
	std::vector<double> v(2);
	v[0] = this->X();
	v[1] = this->Y();

	std::vector<double> rotated = rotate(v, angle);

	return Point2D(rotated[0], rotated[1]);
}

double Point2D::Distance(const Point2D & p2) const
{
	return sqrt((p2.X() - this->X()) * (p2.X() - this->X()) + 
		(p2.Y() - this->Y()) * (p2.Y() - this->Y()));
}

bool operator==(const Point2D & p1, const Point2D & p2)
{
	return (p1.X() == p2.X() && p1.Y() == p2.Y());
}

bool operator!=(const Point2D & p1, const Point2D & p2)
{
	return !(p1 == p2);
}