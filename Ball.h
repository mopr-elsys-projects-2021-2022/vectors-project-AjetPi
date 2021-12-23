#pragma once
#include "Line.h"

class Ball
{
	friend class Field;
	
	friend istream& operator>>(istream& in, Ball& b)
	{
		cout << "Starting point of ball: ";
		in >> b.startingPoint;
		b.trajectory = Vector((b.center = b.startingPoint));
		cout << "Diameter of ball: ";
		in >> b.diameter;
		b.radius = b.diameter / 2;
		
		return in;
	}
	friend ostream& operator<<(ostream& out, const Ball& b)
	{
		out << "Ball center - " << b.center << endl;
		out << "Ball diameter - " << b.diameter << endl;
		
		return out;
	}
	
	private:
		double diameter, radius;
		Point startingPoint, center;
		Vector trajectory;
		Line equation; // Line between ball center and trajectory
		
	public:
		Ball(double diameter, const Point& startingPoint) : diameter(diameter), radius(diameter / 2), startingPoint(startingPoint), center(startingPoint), trajectory(startingPoint), equation() {}
		Ball() : Ball(0, Point()) {}
};
