#pragma once
#include "Ball.h"
#include "Line.h"
#define FOUR 4

class Field
{
	private:
		Ball ball;
		Point startingPoint;
		Point endPoints[FOUR];
		Line sideWalls[FOUR];
		double width, height;
		
		friend ostream& operator<<(ostream& out, const Field& f);
		
	public:
		Field();
		Field(const Point&, double, double, const Ball&);
		Field(Point(&)[4], const Ball&);
		
		void hit(const Point&, double);
		static bool checkBall(const Ball& ball);
		static bool checkWidthHeight(double, double);
		static bool checkEndPoints(Point(&)[FOUR]);
		static void ballCase(Field&);
		static void simpleCase(Field&);
		static void complexCase(Field&);
};
