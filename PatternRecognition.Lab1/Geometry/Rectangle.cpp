#include "Rectangle.h"

Rectangle2D::Rectangle2D()
{
	_vertexes = std::vector<Point2D>(4, Point2D());
}

Rectangle2D::Rectangle2D(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Point2D& p4)
{
	_vertexes.reserve(4);
	_vertexes.push_back(p1);
	_vertexes.push_back(p2);
	_vertexes.push_back(p3);
	_vertexes.push_back(p4);
}

Rectangle2D::Rectangle2D(const Rectangle2D& r)
{
	_vertexes.reserve(4);
	_vertexes.push_back(r._vertexes[0]);
	_vertexes.push_back(r._vertexes[1]);
	_vertexes.push_back(r._vertexes[2]);
	_vertexes.push_back(r._vertexes[3]);
}

bool Compare_Points_by_Y(const Point2D & p1, const Point2D & p2)
{
	return p1.Y() < p2.Y();
};

std::vector<Point2D>* Sort_by_Y(const std::vector<Point2D> & points)
{
	std::vector<Point2D>* sorted_points = new std::vector<Point2D>(points);
	std::sort(sorted_points->begin(), sorted_points->end(), Compare_Points_by_Y);
	return sorted_points;
}

int Rectangle2D::LeftBottomIndex() const
{
	std::vector<Point2D>* byY = Sort_by_Y(_vertexes);
	Point2D& leftBottom = byY->at(0);
	if (byY->at(0).Y() == byY->at(1).Y())
		leftBottom = byY->at(0).X() < byY->at(1).X() ? byY->at(0) : byY->at(1);
	int leftBottomIndex = 0;
	for (int i = 0; i < 4; ++i)
		if (leftBottom == _vertexes[i]) leftBottomIndex = i;
	return leftBottomIndex;
}

Rectangle2D Rectangle2D::Scale(const double& xCoef, const double& yCoef) const
{
	return Rectangle2D(_vertexes[0].Scale(xCoef, yCoef), _vertexes[1].Scale(xCoef, yCoef),
		_vertexes[2].Scale(xCoef, yCoef), _vertexes[3].Scale(xCoef, yCoef));
}

Rectangle2D Rectangle2D::Translation(const double& byX, const double& byY)const
{
	return Rectangle2D(_vertexes[0].Translation(byX, byY), _vertexes[1].Translation(byX, byY),
		_vertexes[2].Translation(byX, byY), _vertexes[3].Translation(byX, byY));
}

Rectangle2D Rectangle2D::Rotate(const double& angle) const
{
	Point2D rotatedP1 = _vertexes[0].Rotate(angle);
	Point2D rotatedP2 = _vertexes[1].Rotate(angle);
	Point2D rotatedP3 = _vertexes[2].Rotate(angle);
	Point2D rotatedP4 = _vertexes[3].Rotate(angle);
	return Rectangle2D(rotatedP1, rotatedP2, rotatedP3, rotatedP4);
}