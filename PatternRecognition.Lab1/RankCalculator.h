#pragma once

#include <vector>
#include "Geometry/Geometry.h"

enum DirectionOfCompression { Left, Right, Centre };

class RankCalculator
{
	public:

		std::vector<int> GetRanks(const std::vector<Point2D> & points, 
			DirectionOfCompression directionOfCompression, 
			bool chooseGravityCentre);
		
	private:

		Rectangle2D GetRectangle(const std::vector<Point2D> & points);

		void FindFarthestPair(const std::vector<Point2D> & points, 
			Point2D & diag1, Point2D & diag2, double & distance);

		void FindFarthestFromLine(Line2D l, const std::vector<Point2D> & points, Point2D & top, 
			Point2D & bottom, double & maxTop, double & maxBot);

		std::vector<Point2D> RotatePoints(const std::vector<Point2D> & points, const double & angle);

		std::vector<Point2D> TranslatePoints(const std::vector<Point2D> & points, const double & xOffset, 
			const double & yOffset);

		std::vector<Point2D> ScalePoints(const std::vector<Point2D> & points, const double & byX, const double & byY);

		void GetParameters(const Rectangle2D & rect, std::vector<double> & offset, 
			std::vector<double> & rectParams, double & angle);

		std::vector<std::pair<double, int>> GetRadiuses(const std::vector<Point2D> & points, const Point2D & centre);

		std::vector<int> GetOrder(const std::vector<Point2D> & points, const Point2D & centre);
		
		double GetRadius(const std::vector<Point2D> & points, const Point2D & centre);

		void TransformToOrigin(const Rectangle2D & rect, const std::vector<Point2D> & points,
			std::vector<double> & rectParams, std::vector<Point2D> & modifiedPoints);

		void TransformToRight(const Rectangle2D & rect, const std::vector<Point2D> & points,
			std::vector<Point2D> & modifiedPoints, Point2D & geomCentre);

		void TransformToCentre(const Rectangle2D & rect, const std::vector<Point2D> & points,
			std::vector<Point2D> & modifiedPoints, Point2D & geomCentre);

		void RankCalculator::TransformToLeft(const Rectangle2D & rect, const std::vector<Point2D> & points,
			std::vector<Point2D> & modifiedPoints, Point2D & geomCentre);

		Point2D GetGravityCentre(const std::vector<Point2D> & points);
};