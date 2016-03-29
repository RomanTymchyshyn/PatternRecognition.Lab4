#pragma once

#include "Point.h"

class Point2D: public Point
{
	public:

		Point2D(double x = 0.0, double y = 0.0): Point(2, x, y) {};

		double X() const { return _coords[0]; };

		double Y() const { return _coords[1]; };

		Point2D Rotate(const double & angle) const;

		Point2D Scale(const double & xCoef, const double & yCoef) const { return Point2D(this->X() * xCoef, this->Y() * yCoef);};

		Point2D Translation(const double & byX, const double & byY) const { return Point2D(this->X() + byX, this->Y() + byY); };

		double Distance(const Point2D & p2) const;
};

bool operator==(const Point2D & p1, const Point2D & p2);

bool operator!=(const Point2D & p1, const Point2D & p2);