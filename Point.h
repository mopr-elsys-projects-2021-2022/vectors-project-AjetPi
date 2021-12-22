#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Point
{
	protected:
		double x, y;
		
		friend class Vector;
		friend class Line;
		friend class Field;
		
		friend istream& operator>>(istream& in, Point& p)
		{
			in >> p.x;
			in >> p.y;
			
			return in;
		}
		friend ostream& operator<<(ostream& out, const Point& p)
		{
			out << "(" << p.x << ", " << p.y << ")";
			
			return out;
		}
		
	public:
		Point() : Point(0, 0) {}
		Point(double x, double y) : x(x), y(y) {}
		
		double length(const Point& p)
		{
			return (sqrt(pow(p.x - x, 2) + pow(p.y - y, 2)));
		}
};
