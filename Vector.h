#pragma once
#include "Point.h"

class Vector
{
	private:
		double x, y;
		
		friend class Line;
		friend class Field;
		
	public:
		Vector(double x = 0, double y = 0) : x(x), y(y) {}
		Vector(Point p1 = Point(), Point p2 = Point()) : Vector(p2.x - p1.x, p2.y - p1.y) {}
		
		Vector operator+(const Vector& other);
		Vector operator*(double scalar);
};
