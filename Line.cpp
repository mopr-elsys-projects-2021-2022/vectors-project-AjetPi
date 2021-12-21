#include "Line.h"

double Line::substitute(const Vector& v)
{
	return (sub = A * v.x + B * v.y + C);
}
Vector Line::solve(const Line& other)
{
	double determinant = A * other.B - B * other.A;
	double x, y;
	x = (((-C) * other.B) - (B * (-other.C))) / determinant;
	y = ((A * (-other.C)) - ((-C) * other.A)) / determinant;
	return Vector(x, y);
}
