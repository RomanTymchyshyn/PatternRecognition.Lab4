#pragma once

#include <algorithm>
#include "Point2D.h"
#include "Line2D.h"
#include "GeometryUtilities.h"

class Rectangle2D
{
	public:
		Rectangle2D();
		
		Rectangle2D(const Point2D & p1, const Point2D & p2, const Point2D & p3, const Point2D & p4);
		
		Rectangle2D(const Rectangle2D & r);
				
		Point2D Vertex(const int & i) const { return _vertexes[i]; }
				
		int LeftBottomIndex() const;
		
		Rectangle2D Scale(const double & xCoef, const double & yCoef) const ;
		
		Rectangle2D Translation(const double & byX, const double & byY) const;
		
		Rectangle2D Rotate(const double & angle) const;
		
		~Rectangle2D(){}

	private:

		std::vector<Point2D> _vertexes;
};