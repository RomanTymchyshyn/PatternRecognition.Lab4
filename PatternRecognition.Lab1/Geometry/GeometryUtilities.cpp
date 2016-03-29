#include "GeometryUtilities.h"

std::vector<double> rotate(std::vector<double> a, const double & phi)
{
	double a11 = cos(phi);
	double a12 = sin(phi);
	std::vector< std::vector<double> > matr;
	std::vector< double > result;
	result.push_back(a11);
	result.push_back(a12);
	matr.push_back(result);
	result.clear();
	result.push_back((-1.0) * a12);
	result.push_back(a11);
	matr.push_back(result);
	result.clear();
	result = matr * a;
	return result;
}