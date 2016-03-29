#pragma once

#include <vector>
#include <stdarg.h> 
#include "../Utilities.h"

struct Point
{
	public:

		Point(const int & dim, const double & coord ...);

		Point(const std::vector<double> & coords);

		int Dim() const {return _dim;}

		double Coord(const int & i) const {return i < _dim ? _coords[i] : throw std::invalid_argument("Coordinate number is out of range. Dimension of the point is " + itos(_dim) + "!");}

		Point& operator=(const Point & p);

	protected:
		int _dim;
		std::vector<double> _coords;
};

bool operator==(const Point & p1, const Point & p2);

bool operator!=(const Point & p1, const Point & p2);