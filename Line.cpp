#include "Line.h"

double Line::substitute(const Vector& v)
{
	return A * v.x + B * v.y + C;
}
pair<double, double> Line::solve(const Line& other, double e, double f)
{
	e -= C;
	f -= other.C;
	double determinant = A * other.B - B * other.A;
	pair<double, double> xy;
	if(determinant)
	{
		xy.first = (e * other.B - B * f) / determinant;
		xy.second = (A * f - e * other.A) / determinant;
	}
	return xy;
}
