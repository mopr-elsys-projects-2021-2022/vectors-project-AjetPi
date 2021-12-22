#include "Line.h"

Line::Line() : Line(0, 0, 0) {}
Line::Line(double A, double B, double C) : A(A), B(B), C(C) {}
Line::Line(const Point& p1, const Point& p2) : A(-(p2.y - p1.y)), B(p2.x - p1.x), C(-(A * p1.x + B * p1.y)) {}

double Line::substitute(const Vector& v)
{
	return (sub = A * v.x + B * v.y + C);
}
Vector Line::solve(const Line& other)
{
	double D = A * other.B - B * other.A;
	double x, y;
	x = (((-C) * other.B) - (B * (-other.C))) / D;
	y = ((A * (-other.C)) - ((-C) * other.A)) / D;
	return Vector(x, y);
}
