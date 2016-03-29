#include "Line2D.h"

Line2D::Line2D()
{
	A = 0, B = 1, C = 0;
}

Line2D::Line2D(const double& a, const double& b, const double& c)
{
	if (A == 0 && B == 0) throw;
	A = a, B = b, C = c;
}

Line2D::Line2D(Point2D& p1, Point2D& p2)
{
	A = p2.Y() - p1.Y();
	B = p1.X() - p2.X();
	C = p1.Y() * p2.X() - p2.Y() * p1.X();
}

Line2D::Line2D(const Line2D& l)
{
	this->A = l.A;
	this->B = l.B;
	this->C = l.C;
}

Line2D& Line2D::operator=(const Line2D& l)
{
	this->A = l.A;
	this->B = l.B;
	this->C = l.C;
	return (*this);
}

int Line2D::Deviation(const Point2D& p)
{
	double dev = (A * p.X() + B * p.Y() + C) * (C > 0 ? -1 : 1);
	if (dev > 0.0) return 1;
	if (dev < 0) return -1;
	return 0;
}

double Line2D::Distance(const Point2D& p)
{
	double distance = fabs(p.X() * A + p.Y() * B + C) / sqrt(A*A + B*B);
	return distance;
}

Line2D Line2D::GetParallel(const Point2D& p)
{
	double c = -A * p.X() - B * p.Y();
	Line2D parallel(A, B, c);
	return parallel;
}

Line2D Line2D::GetPerpendicular(const Point2D& p)
{
	double c = -B * p.X() + A * p.Y();
	Line2D perpendicular(B, -A, c);
	return perpendicular;
}

Point2D Line2D::Intersection(const Line2D& l)
{
	double delta = A * l.B - l.A * B;
	double Px = (l.C * B - C * l.B) / delta;
	double Py = (l.A * C - A * l.C) / delta;
	return Point2D(Px, Py);
}