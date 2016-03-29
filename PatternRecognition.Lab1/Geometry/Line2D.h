#pragma once

#include "Point2D.h"

class Line2D
{
	private:
		double A;
		double B;
		double C;
	public:
		Line2D();

		Line2D(const double & a, const double & b, const double & c);
		
		Line2D(Point2D & p1, Point2D & p2);
		
		Line2D(const Line2D & l);
		
		Line2D& operator=(const Line2D & e);
		
		int Deviation(const Point2D & p);
		
		double Distance(const Point2D & p);
		
		Line2D GetParallel(const Point2D & p);
		
		Line2D GetPerpendicular(const Point2D & p);
		
		Point2D Intersection(const Line2D & l);

};