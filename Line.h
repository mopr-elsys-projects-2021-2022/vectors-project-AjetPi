#pragma once
#include "Vector.h"

class Line
{
	private:
		double A, B, C;
		
		friend class Field;
		
	public:
		Line(double A = 0, double B = 0, double C = 0) : A(A), B(B), C(C) {}
		Line(Point p1 = Point(), Point p2 = Point()) : A(-(p2.y - p1.y)), B(p2.x - p1.x), C(-(A * p1.x + B * p1.y)) {}
		
		double substitute(const Vector& v);
		pair<double, double> solve(const Line& other, double e, double f);
};
