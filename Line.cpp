#include "Line.h"

Line::Line(double A, double B, double C) : A(A), B(B), C(C), D(0) {}
Line::Line(const Line& other) : Line(other.A, other.B, other.C - other.D) {}
Line::Line(const Line& other, const Point& p) : A(-(other.A)), B(-(other.B)), C(-((A * p.x) + (B * p.y))), D(0) {}
Line::Line(const Point& p1, const Point& p2) : A(-(p2.y - p1.y)), B(p2.x - p1.x), C(-((A * p1.x) + (B * p1.y))), D(0) {}
Line::Line() : Line(0, 0, 0) {}

bool Line::perpendicular(const Line& other)
{
	return (bool)(((A * other.A) + (B * other.B)) == 0);
}
bool Line::parallel(const Line& other)
{
	if(((A == 0) && (other.A == 0)) || ((B == 0) && (other.B == 0)))
	{
		return true;
	}
	return (bool)(((A / other.A) == (B / other.B)) && ((A / other.A) != (C / other.C)));
}

double Line::substitute(const Point& p)
{
	return (D = (A * p.x) + (B * p.y) + C);
}
Point Line::solve(const Line& other) const
{
	double determinant = (A * other.B) - (B * other.A);
	Point p;
	p.x = (((-C) * other.B) - (B * (-other.C))) / determinant;
	p.y = ((A * (-other.C)) - ((-C) * other.A)) / determinant;
	return p;
}
