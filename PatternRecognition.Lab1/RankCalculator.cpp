#include "RankCalculator.h"
#include <algorithm>
#include <fstream>

std::vector<int> RankCalculator::GetRanks(const std::vector<Point2D> & points, 
	DirectionOfCompression directionOfCompression, 
	bool chooseGravityCentre)
{
	Rectangle2D rect = GetRectangle(points);
	
	Rectangle2D modifiedRect;
	std::vector<Point2D> modifiedPoints;
	Point2D geomCentre;

	switch(directionOfCompression)
	{
		case Right:
			TransformToRight(rect, points, modifiedPoints, geomCentre);
			break;

		case Left:
			TransformToLeft(rect, points, modifiedPoints, geomCentre);
			break;

		case Centre:
			TransformToCentre(rect, points, modifiedPoints, geomCentre);
			break;
	}
	
	Point2D centre = chooseGravityCentre ? GetGravityCentre(modifiedPoints) : geomCentre;

	std::vector<int> ranks = GetOrder(modifiedPoints, centre);
	
	return ranks;
}

Point2D RankCalculator::GetGravityCentre(const std::vector<Point2D> & points)
{
	double x = 0, y = 0;
	int size = points.size();
	for (int i = 0; i < size; ++i)
	{
		x += points[i].X();
		y += points[i].Y();
	}
	x/=size;
	y/=size;
	return Point2D(x, y);
}

Rectangle2D RankCalculator::GetRectangle(const std::vector<Point2D> & points)
{
	Point2D left, right;
	double distance = 0.0;
	FindFarthestPair(points, left, right, distance);

	Line2D L(left, right);
	Point2D top(left), bottom(right);
	double maxTopDist, maxBotDist;
	FindFarthestFromLine(L, points, top, bottom, maxTopDist, maxBotDist);

	if (top == left)
		top = left.Y() > right.Y() ? left : right;
	if (bottom == right)
		bottom = left.Y() < right.Y() ? left : right;

 	Line2D L1 = L.GetParallel(top);
	Line2D L2 = L.GetParallel(bottom);
	Line2D L3 = L.GetPerpendicular(left);
	Line2D L4 = L.GetPerpendicular(right);

	Point2D p1 = L1.Intersection(L3);
	Point2D p2 = L1.Intersection(L4);
	Point2D p3 = L2.Intersection(L4);
	Point2D p4 = L2.Intersection(L3);

	return Rectangle2D(p1, p2, p3, p4);
}

void RankCalculator::FindFarthestPair(const std::vector<Point2D> & points, Point2D & diag1, 
	Point2D & diag2, double & distance)
{
	int n = points.size();
	distance = -1;
	for (int i = 0; i < n; ++i)
	{
		Point2D p1 = points[i];
		for (int j = i + 1; j < n; ++j)
		{
			Point2D p2 = points[j];
			double dist = p1.Distance(p2);
			if (dist > distance)
			{
				diag1 = p1;
				diag2 = p2;
				distance = dist;
			}
		}
	}
	return;
}

void RankCalculator::FindFarthestFromLine(Line2D l, const std::vector<Point2D> & points, Point2D & top, 
	Point2D & bottom, double & maxTop, double & maxBot)
{
	int n = points.size();
	maxTop = -1, maxBot = -1;
	for (int i = 0; i < n; ++i)
	{
		Point2D p = points[i];
		double dist = l.Distance(p);
		int deviation = l.Deviation(p);
		if (deviation == -1)
		{
			if (dist > maxTop)
			{
				top = p;
				maxTop = dist;
			}
		}
		else if (deviation == 1)
		{
			if (dist > maxBot)
			{
				bottom = p;
				maxBot = dist;
			}
		}
	}
	return;
}

std::vector<Point2D> RankCalculator::RotatePoints(const std::vector<Point2D> & points, const double & angle)
{
	int size = points.size();
	std::vector<Point2D> res;
	res.reserve(size);
	for (int i = 0; i < size; ++i)
		res.push_back(points[i].Rotate(angle));
	return res;
}

std::vector<Point2D> RankCalculator::TranslatePoints(const std::vector<Point2D> & points, 
	const double & xOffset, const double & yOffset)
{
	int size = points.size();
	std::vector<Point2D> res;
	res.reserve(size);
	for (int i = 0; i < size; ++i)
		res.push_back(points[i].Translation(xOffset, yOffset));
	return res;
}

std::vector<Point2D> RankCalculator::ScalePoints(const std::vector<Point2D> & points, const double & byX, const double & byY)
{
	int size = points.size();
	std::vector<Point2D> res;
	res.reserve(size);
	for (int i = 0; i < size; ++i)
		res.push_back(points[i].Scale(byX, byY));
	return res;
}

double RankCalculator::GetRadius(const std::vector<Point2D> & points, const Point2D & centre)
{
	double max = -1;
	int size = points.size();
	std::vector<Point2D> res;
	res.reserve(size);
	for (int i = 0; i < size; ++i)
	{
		double dist = points[i].Distance(centre);
		if (dist > max) max = dist;
	}
	return max;
}

bool Compare_Pair(const std::pair<double, int> & p1, const std::pair<double, int> & p2)
{
	return p1.first < p2.first;
};

std::vector<std::pair<double, int>> RankCalculator::GetRadiuses(const std::vector<Point2D> & points, const Point2D & centre)
{
	int size = points.size();
	std::vector<std::pair<double, int>> radiuses;
	radiuses.reserve(size);
	for (int i = 0; i < size; ++i)
	{
		double dist = points[i].Distance(centre);
		radiuses.push_back(std::make_pair(dist, i + 1));
	}
	sort(radiuses.begin(), radiuses.end(), Compare_Pair);
	return radiuses;
}

std::vector<int> RankCalculator::GetOrder(const std::vector<Point2D> & points, const Point2D & centre)
{
	std::vector<std::pair<double, int>> radiuses = GetRadiuses(points, centre);

	int size = points.size();
	std::vector<int> result(size, 0);
	for(int i = 0; i < size; ++i)
	{
		result[i] = radiuses[i].second;
	}

	return result;
}

void RankCalculator::GetParameters(const Rectangle2D & rect, std::vector<double> & offset, 
	std::vector<double> & rectParams, double & angle)
{
	int leftBottomIndex = rect.LeftBottomIndex();
	offset.push_back(-rect.Vertex(leftBottomIndex).X());
	offset.push_back(-rect.Vertex(leftBottomIndex).Y());

	int neighbour1 = leftBottomIndex == 0 ? 3 : leftBottomIndex - 1;
	int neighbour2 = leftBottomIndex == 3 ? 0 : leftBottomIndex + 1;
	int secondPoint = rect.Vertex(neighbour1).X() > rect.Vertex(neighbour2).X() ? neighbour1 : neighbour2;
	double a1 = rect.Vertex(secondPoint).X() - rect.Vertex(leftBottomIndex).X();
	double a2 = rect.Vertex(secondPoint).Y() - rect.Vertex(leftBottomIndex).Y();
	angle = acos(a1 / sqrt(a1 * a1 + a2 * a2));
	if (a2 < 0) angle *= -1.0;

	rectParams.push_back(rect.Vertex(secondPoint).Distance(rect.Vertex(leftBottomIndex)));
	rectParams.push_back(rect.Vertex(secondPoint == neighbour1 ? neighbour2 : neighbour1).Distance( 
		rect.Vertex(leftBottomIndex)));
}

void RankCalculator::TransformToOrigin(const Rectangle2D & rect, const std::vector<Point2D> & points,
	std::vector<double> & rectParams, std::vector<Point2D> & modifiedPoints)
{
	std::vector<double> offset;
	double angle;
	GetParameters(rect, offset, rectParams, angle);

	modifiedPoints = TranslatePoints(points, offset[0], offset[1]);

	modifiedPoints = RotatePoints(modifiedPoints, angle);
}

void RankCalculator::TransformToRight(const Rectangle2D & rect, const std::vector<Point2D> & points,
	std::vector<Point2D> & modifiedPoints, Point2D & geomCentre)
{
	std::vector<double> rectParams;
	TransformToOrigin(rect, points, rectParams, modifiedPoints);

	double alpha = rectParams[1] / rectParams[0];

	modifiedPoints = ScalePoints(modifiedPoints, alpha, 1.0);

	geomCentre = Point2D(rectParams[1] / 2.0, rectParams[1] / 2.0);
}

void RankCalculator::TransformToLeft(const Rectangle2D & rect, const std::vector<Point2D> & points,
	std::vector<Point2D> & modifiedPoints, Point2D & geomCentre)
{
	std::vector<double> rectParams;
	TransformToOrigin(rect, points, rectParams, modifiedPoints);

	modifiedPoints = TranslatePoints(modifiedPoints, -rectParams[0], 0);

	double alpha = rectParams[1] / rectParams[0];

	modifiedPoints = ScalePoints(modifiedPoints, alpha, 1.0);

	geomCentre = Point2D(-rectParams[1] / 2.0, rectParams[1] / 2.0);
}

void RankCalculator::TransformToCentre(const Rectangle2D & rect, const std::vector<Point2D> & points,
	std::vector<Point2D> & modifiedPoints, Point2D & geomCentre)
{
	std::vector<double> rectParams;
	TransformToOrigin(rect, points, rectParams, modifiedPoints);

	modifiedPoints = TranslatePoints(modifiedPoints, -rectParams[0] / 2.0, 0);

	double alpha = rectParams[1] / rectParams[0];

	modifiedPoints = ScalePoints(modifiedPoints, alpha, 1.0);

	geomCentre = Point2D(0, rectParams[1] / 2.0);
}