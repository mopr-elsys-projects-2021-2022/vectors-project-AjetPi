#pragma once
#include "Point.h"

class Vector : private Point // Inherit x and y coordinate variables
{
	friend class Field;
	
	public:
		Vector(double, double);
		Vector(const Point&);
		Vector(const Point&, const Point&); // Vector between two points
		Vector();
		
		Vector& operator+=(const Vector&);
		Vector operator*(double) const;
};
