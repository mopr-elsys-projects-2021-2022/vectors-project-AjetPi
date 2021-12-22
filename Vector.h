#pragma once
#include "Point.h"

class Vector : private Point // Inherit coordinates
{
	private:
		friend class Field;
		
	public:
		Vector();
		Vector(const Point&);
		Vector(double, double);
		Vector(const Point&, const Point&); // Vector between two points
		
		Vector operator+(const Vector&);
		Vector operator*(double);
};
