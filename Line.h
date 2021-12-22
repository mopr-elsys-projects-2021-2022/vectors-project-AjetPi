#pragma once
#include "Vector.h"

class Line
{
	private:
		double A, B, C;
		double sub;
		
		friend class Field;
		
	public:
		Line();
		Line(double, double, double);
		Line(const Point&, const Point&);
		
		double substitute(const Vector&);
		Vector solve(const Line&);
};
