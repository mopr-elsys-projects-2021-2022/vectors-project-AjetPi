#pragma once
#include "Ball.h"
#define POINTS 4

class Field
{
	private:
		Ball ball;
		Point startingPoint;
		Point endPoints[POINTS];
		double width, height;
		// Line sideWalls[4];
		
		friend ostream& operator<<(ostream& out, const Field& f);
		
	public:
		Field();
		Field(const Point&, double, double, const Ball&);
		Field(Point(&)[4], const Ball&);
		
		void hit(const Point&, double);
		static bool checkBall(const Ball& ball);
		static bool checkWidthHeight(double, double);
		static bool checkEndPoints(Point(&)[POINTS]);
		static void ballCase(Field&);
		static void simpleCase(Field&);
		static void complexCase(Field&);
};
