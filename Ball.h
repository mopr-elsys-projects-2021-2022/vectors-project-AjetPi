#pragma once
#include "Point.h"

class Ball
{
	private:
		Point center;
		double diameter;
		
		friend class Field;
		friend istream& operator>>(istream& in, Ball& b)
		{
			cout << "Starting point of ball: ";
			in >> b.center;
			cout << "Diameter of ball: ";
			in >> b.diameter;
			
			return in;
		}
		friend ostream& operator<<(ostream& out, const Ball& b)
		{
			out << "Ball center - " << b.center << endl;
			out << "Ball diameter - " << b.diameter << endl;
			
			return out;
		}
		
	public:
		Ball() : Ball(Point(), 0) {}
		Ball(const Point& center, double diameter) : center(center), diameter(diameter) {}
		
		double radius()
		{
			return (diameter / 2);
		}
};
