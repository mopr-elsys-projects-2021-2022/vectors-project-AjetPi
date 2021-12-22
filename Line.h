#pragma once
#include "Vector.h"

class Line
{
	private:
		double A, B, C; // Coordinate coefficients and free member
		double D; // Equation solution
		
		friend class Field;
		
	public:
		Line();
		Line(const Line&);
		Line(double, double, double);
		Line(const Line&, const Point&); // Parallel line through point
		Line(const Point&, const Point&); // Line through two points
		
		double substitute(const Point&); // Substitute coordinates in equation
		Point solve(const Line&) const; // Solve system of two equations with two unknown coordinates
};
