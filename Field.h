#pragma once
#include "Ball.h"
#define FOUR 4 // Points and walls

class Field
{
	friend ostream& operator<<(ostream& out, const Field& f);
	
	private:
		bool ratioFlag = false; // Flag whether modify function has been called or not
		double width, height, widthRatio, heightRatio; // Left-hand side free member of equation to width or height ratio
		Point endPoints[FOUR];
		Line sideWalls[FOUR]; // Field wall equations
		Ball ball;
		
	public:
		Field(double, double, const Point&, const Ball&);
		Field(Point(&)[FOUR], const Ball&);
		Field();
		
		bool checkFieldRatio(double, double); // Check whether field width to height ratio equals two or half
		bool checkFieldPoints(Point(&)[FOUR]); // Check whether field points create a rectangle
		bool checkBallCenter(const Ball&); // Check whether ball center lies in field
		bool checkBallDiameter(const Ball&); // Check whether ball diameter is signed
		bool checkPower(double); // Check whether power is between one and ten
		
		void modify(); // Modify all equations' left-hand side free member to take ball radius into account
		void hit(const Point&, double);
		
		static void ballCase(Field&); // Change ball parameters
		static void simpleCase(Field&); // Change field parameters with width and height as a reference
		static void complexCase(Field&); // Change field parameters with field points as a reference
};
