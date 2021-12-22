#pragma once
#include "Point.h"

class Vector : private Point
{
	private:
		friend class Line;
		friend class Field;
		
	public:
		Vector();
		Vector(double, double);
		Vector(const Point&, const Point&);
		
		Vector operator+(const Vector&);
		Vector operator*(double);
};
