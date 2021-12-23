#pragma once
#include "Vector.h"

class Line
{
	friend class Field;
	
	private:
		double A, B, C, D; // Left-hand side members and right-hand side member of equation
		
	public:
		Line(double, double, double);
		Line(const Line&); // Copy constructor that takes the right-hand side member of an equation into account
		Line(const Line&, const Point&); // Parallel line through point
		Line(const Point&, const Point&); // Line through two points
		Line();
		
		bool parallel(const Line&); // Check whether two lines are parallel
		bool perpendicular(const Line&); // Check whether two line are perpendicular
		
		double substitute(const Point&); // Substitute coordinates in equation
		Point solve(const Line&) const; // Solve system of two equations with two unknown coordinates
};
