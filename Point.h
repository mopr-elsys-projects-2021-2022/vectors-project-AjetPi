#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Point
{
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
	
	protected:
		double x, y;
		
	public:
		Point(double x, double y) : x(x), y(y) {}
		Point(const Point& p) : Point(p.x, p.y) {}
		Point(const Point& p1, const Point& p2) : Point(p2.x - p1.x, p2.y - p1.y) {}
		Point() : Point(0, 0) {}
		
		double length(const Point& p) const // Length between two points
		{
			return (sqrt(pow(p.x - x, 2) + pow(p.y - y, 2)));
		}
};
