#include "Point.h"

Point::Point(const int & dim, const double & coord ...)
{
	_dim = dim;
	_coords = std::vector<double>();
	_coords.reserve(_dim);

	va_list v1;
	va_start(v1, coord);
	double current = coord;
	for (int i = 0; i < _dim; ++i)
	{
		_coords.push_back(current);
		current = va_arg(v1, double);
	}
	va_end(v1);

	return;
}

Point::Point(const std::vector<double> & coords)
{
	_dim = coords.size();

	_coords = std::vector<double>(_dim, 0);

	for (int i = 0; i < _dim; ++i)
		_coords[i] = coords[i];
}

Point& Point::operator=(const Point & p)
{
	_dim = p.Dim();
	_coords = p._coords;
	return (*this);
}

bool operator==(const Point & p1, const Point & p2)
{
	if (p1.Dim() != p2.Dim())
		return false;

	for (int i = 0; i < p1.Dim(); ++i)
	{
		if (p1.Coord(i) != p2.Coord(i))
			return false;
	}

	return true;
}

bool operator!=(const Point & p1, const Point & p2)
{
	return !(p1 == p2);
}