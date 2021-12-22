#include "Field.h"

Field::Field() {}
Field::Field(const Point& origin, double width, double height, const Ball& ball) : ball(ball), startingPoint(ball.center), width(width), height(height)
{
	endPoints[0] = Point(origin.x, origin.y); // A
	endPoints[1] = Point(origin.x + width, origin.y); // B
	endPoints[2] = Point(origin.x + width, origin.y + height); // C
	endPoints[3] = Point(origin.x, origin.y + height); // D
	
	sideWalls[0] = Line(endPoints[0], endPoints[1]); // AB
	sideWalls[1] = Line(endPoints[1], endPoints[2]); // BC
	sideWalls[2] = Line(sideWalls[0], endPoints[2]); // CD
	sideWalls[3] = Line(sideWalls[1], endPoints[3]); // DA
}
Field::Field(Point(& endPoints)[FOUR], const Ball& ball) : ball(ball), startingPoint(ball.center)
{
	for (int i = 0; i < FOUR; ++i)
	{
		this->endPoints[i] = endPoints[i];
	}
	
	sideWalls[0] = Line(endPoints[0], endPoints[1]);
	sideWalls[1] = Line(endPoints[1], endPoints[2]);
	sideWalls[2] = Line(sideWalls[0], endPoints[2]);
	sideWalls[3] = Line(sideWalls[1], endPoints[3]);
	
	width = endPoints[0].length(endPoints[1]);
	height = endPoints[3].length(endPoints[0]);
}

void Field::hit(const Point& target, double power)
{
	if((power < 1) || (power > 10))
	{
		cout << "Invalid power. Try again." << endl;
		return;
	}
	
	bool someOtherFlag = 1;
	double radius = ball.radius();
	double wratio = abs(sideWalls[3].C - sideWalls[1].C) / width;
	double hratio = abs(sideWalls[2].C - sideWalls[0].C) / height;
	for(int i = 0; i < FOUR; ++i)
	{
		sideWalls[i].C -= radius * ((hratio * !(i % 2)) + (wratio * (i % 2)));
	}
	Vector trajectory = Vector(ball.center.x, ball.center.y) + Vector(ball.center, target) * power;
	
	bool flag = 1;
	while(flag)
	{
		Line trj(ball.center, (Point)trajectory);
		for(int i = 0; i < FOUR; ++i)
		{
			trj.substitute(endPoints[i]);
			if((trj.D < 0.001) && (trj.D >= 0))
			{
				if(signbit(trajectory.x - ball.center.x) != signbit(endPoints[i].x - ball.center.x))
				{
					continue;
				}
				if(abs(trajectory.x - ball.center.x) >= abs(endPoints[i].x - ball.center.x))
				{
					ball.center = startingPoint;
					flag = 0;
					return;
				}
				if(someOtherFlag)
				{
					someOtherFlag = 0;
					for(int i = 0; i < FOUR; ++i)
					{
						sideWalls[i].C += radius * ((hratio * !(i % 2)) + (wratio * (i % 2)));
					}
				}
				break;
			}
		}
		
		for(int i = 0; i < FOUR; ++i)
		{
			sideWalls[i].substitute((Point)trajectory);
		}
		int i;
		double min = 0;
		for(int y = 0; y < FOUR; ++y)
		{
			if(sideWalls[y].D < min)
			{
				i = y;
				min = sideWalls[y].D;
			}
		}
		if(min)
		{
			sideWalls[i].D = -(sideWalls[i].D);
			Line tmp(sideWalls[i]);
			ball.center = sideWalls[i].solve(trj);
			cout << "The ball bounced into the wall at " << ball.center << endl;
			trajectory = tmp.solve(Line(sideWalls[(i + 1) % 4]));
			continue;
		}
		
		flag = 0;
	}
	ball.center = (Point)trajectory;
}

bool Field::checkBall(const Ball& ball)
{
	return (bool)(ball.diameter >= 0);
}
bool Field::checkWidthHeight(double width, double height)
{
	return (bool)(((width / height) == 2) || ((width / height) == 0.5));
}
bool Field::checkEndPoints(Point(& endPoints)[FOUR])
{
	return true;
}

void Field::ballCase(Field& f)
{
	Ball ball;
	cin >> ball;
	if(!Field::checkBall(ball))
	{
		cout << "Invalid ball. Try again." << endl;
		return;
	}
	
	f = Field(f.endPoints, ball);
}
void Field::simpleCase(Field& f)
{
	Point origin;
	cout << "Point of origin of field: ";
	cin >> origin;
	
	double width, height;
	cout << "Width and height of field: ";
	cin >> width >> height;
	if(!Field::checkWidthHeight(width, height))
	{
		cout << "Invalid width and height. Try again." << endl;
		return;
	}
	
	Ball ball;
	cin >> ball;
	if(!Field::checkBall(ball))
	{
		cout << "Invalid ball. Try again." << endl;
		return;
	}
	
	f = Field(origin, width, height, ball);	
}
void Field::complexCase(Field& f)
{
	Point endPoints[FOUR];
	cout << "Field points: " << endl;
	for (int i = 0; i < FOUR; ++i)
	{
		cout << "  " << i + 1 << ") ";
		cin >> endPoints[i];
	}
	
	double width = endPoints[0].length(endPoints[1]);
	double height = endPoints[3].length(endPoints[0]);
	if(!Field::checkWidthHeight(width, height))
	{
		cout << "Invalid width and height. Try again." << endl;
		return;
	}
	
	Ball ball;
	cin >> ball;
	if(!Field::checkBall(ball))
	{
		cout << "Invalid ball. Try again." << endl;
		return;
	}
	
	f = Field(endPoints, ball);
}

ostream& operator<<(ostream& out, const Field& f)
{
	out << "Field points:" << endl;
	for(int i = 0; i < FOUR; ++i)
	{
		out << "  " << f.endPoints[i] << endl;
	}
	out << f.ball;
	
	return out;
}
