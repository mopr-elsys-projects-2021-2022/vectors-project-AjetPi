#include "Line.h"

Line::Line() : Line(0, 0, 0) {}
Line::Line(const Line& l) : Line(l.A, l.B, l.C - l.D) {}
Line::Line(double A, double B, double C) : A(A), B(B), C(C), D(0) {}
Line::Line(const Line& l, const Point& p) : A(-(l.A)), B(-(l.B)), C(-((A * p.x) + (B * p.y))), D(0) {}
Line::Line(const Point& p1, const Point& p2) : A(-(p2.y - p1.y)), B(p2.x - p1.x), C(-((A * p1.x) + (B * p1.y))), D(0) {}

double Line::substitute(const Point& p)
{
	return (D = (A * p.x) + (B * p.y) + C);
}
Point Line::solve(const Line& other) const
{
	double D = (A * other.B) - (B * other.A); // Determinant
	Point p;
	p.x = (((-C) * other.B) - (B * (-other.C))) / D;
	p.y = ((A * (-other.C)) - ((-C) * other.A)) / D;
	return p;
}
