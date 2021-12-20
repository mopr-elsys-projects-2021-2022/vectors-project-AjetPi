#pragma once
#include "Ball.h"

class Field
{
	private:
		Ball ball;
		Point startingPoint;
		Point endPoints[4];
		
	public:
		Field() {}
		Field(Point origin, double width, double height, Ball ball);
		Field(Point endPoints[4], Ball ball);
		
		void hit(Point target, double power);
		
		friend void ballCase(Field& f);
		friend void simpleCase(Field& f);
		friend void complexCase(Field& f);
		
		friend ostream& operator<<(ostream& out, const Field& f);
};
