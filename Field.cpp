#include "Field.h"

Field::Field(double width, double height, const Point& origin, const Ball& ball) : width(width), height(height), ball(ball)
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
Field::Field(Point(& endPoints)[FOUR], const Ball& ball) : ball(ball)
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
	height = endPoints[1].length(endPoints[2]);
}
Field::Field() {}

bool Field::checkFieldRatio(double width, double height)
{
	return (bool)(((width / height) == 2) || ((width / height) == 0.5));
}
bool Field::checkFieldPoints(Point(& endPoints)[FOUR])
{
	Line tmpWalls[FOUR];
	for(int i = 0; i < FOUR; ++i)
	{
		tmpWalls[i] = Line(endPoints[i], endPoints[(i + 1) % FOUR]);
	}
	if(!((tmpWalls[0].parallel(tmpWalls[2])) && (tmpWalls[1].parallel(tmpWalls[3])) && (tmpWalls[0].perpendicular(tmpWalls[1]))))
	{
		return false;
	}
	
	double width = endPoints[0].length(endPoints[1]);
	double height = endPoints[1].length(endPoints[2]);
	if((width != endPoints[2].length(endPoints[3])) || (height != endPoints[3].length(endPoints[0])))
	{
		return false;
	}
	
	return checkFieldRatio(width, height);
}
bool Field::checkBallCenter(const Ball& ball)
{
	for(int i = 0; i < FOUR; ++i)
	{
		if((sideWalls[i].substitute(ball.center)) < 0)
		{
			return false;
		}
	}
	
	return true;
}
bool Field::checkBallDiameter(const Ball& ball)
{
	return (bool)(ball.diameter >= 0);
}
bool Field::checkPower(double power)
{
	return (bool)((power >= 1) && (power <= 10));
}

void Field::modify()
{
	if(!ratioFlag)
	{
		widthRatio = abs(sideWalls[3].C - sideWalls[1].C) / width;
		heightRatio = abs(sideWalls[2].C - sideWalls[0].C) / height;
		for(int i = 0; i < FOUR; ++i)
		{
			sideWalls[i].C -= ball.radius * ((heightRatio * !(i % 2)) + (widthRatio * (i % 2)));
		}
	}
	else
	{
		for(int i = 0; i < FOUR; ++i)
		{
			sideWalls[i].C += ball.radius * ((heightRatio * !(i % 2)) + (widthRatio * (i % 2)));
		}
	}
	
	ratioFlag = !ratioFlag;
}
void Field::hit(const Point& target, double power)
{
	if(!Field::checkPower(power))
	{
		cout << "Invalid power. Try again." << endl;
		return;
	}
	
	modify();
	ball.trajectory += Vector(ball.center, target) * power; // Change ball trajectory
	
	bool flag = true;
	while(flag)
	{
		ball.equation = Line(ball.center, (Point)ball.trajectory);
		for(int i = 0; i < FOUR; ++i)
		{
			ball.equation.substitute(endPoints[i]);
			if((ball.equation.D < 0.001) && (ball.equation.D >= 0)) // Right-hand side free member of equation could equal an insignificantly small fraction
			{
				if(signbit(ball.trajectory.x - ball.center.x) != signbit(endPoints[i].x - ball.center.x)) // Check whether the distances between these points are of the same sign
				{
					continue;
				}
				
				modify(); // No longer take ball radius into account
				if(abs(ball.trajectory.x - ball.center.x) >= abs(endPoints[i].x - ball.center.x)) // Check if distance between points is short enough for the ball to enter the corner
				{
					ball = Ball(ball.diameter, ball.startingPoint); // Return the ball to its starting position
					flag = false;
					return;
				}
				break;
			}
		}
		
		for(int i = 0; i < FOUR; ++i)
		{
			sideWalls[i].substitute((Point)ball.trajectory);
		}
		int i; // Potential wall index
		double min = 0; // Find the lowest right-hand side free member
		for(int y = 0; y < FOUR; ++y)
		{
			if(sideWalls[y].D < min) // This will only occur if we have a negative value
			{
				i = y;
				min = sideWalls[y].D;
			}
		}
		if(min) // If a negative value has been saved ergo if the ball's trajectory passes a wall
		{
			sideWalls[i].D = -(sideWalls[i].D);
			Line tmp(sideWalls[i]); // "Mirror" line which insures that the ball will be on the opposite side of the wall
			ball.center = sideWalls[i].solve(ball.equation); // Set ball center to ricochet or bounce point
			cout << "The ball bounced into the wall at " << ball.center << endl; // Informatory message
			ball.trajectory = tmp.solve(Line(sideWalls[(i + 1) % FOUR])); // Set new ball trajectory after ricochet
			continue;
		}
		
		flag = 0;
	}
	
	if(ratioFlag)
	{
		modify();
	}
	ball.center = (Point)ball.trajectory; // Finalise ball center position
}

void Field::ballCase(Field& f)
{
	Ball ball;
	cin >> ball;
	if(!(f.checkBallCenter(ball)))
	{
		cout << "Invalid ball center. Try again." << endl;
		return;
	}
	if(!(f.checkBallDiameter(ball)))
	{
		cout << "Invalid ball diameter. Try again." << endl;
		return;
	}
	f.ball = ball;
}
void Field::simpleCase(Field& f)
{
	Point origin;
	cout << "Point of origin of field: ";
	cin >> origin;
	double width, height;
	cout << "Width and height of field: ";
	cin >> width >> height;
	if(!(f.checkFieldRatio(width, height)))
	{
		cout << "Invalid width and height. Try again." << endl;
		return;
	}
	f = Field(width, height, origin, Ball());
	
	Ball ball;
	cin >> ball;
	if(!(f.checkBallCenter(ball)))
	{
		cout << "Invalid ball center. Try again." << endl;
		return;
	}
	if(!(f.checkBallDiameter(ball)))
	{
		cout << "Invalid ball diameter. Try again." << endl;
		return;
	}
	f.ball = ball;
}
void Field::complexCase(Field& f)
{
	Point endPoints[FOUR];
	cout << "Field points: " << endl;
	for(int i = 0; i < FOUR; ++i)
	{
		cout << "  " << i + 1 << ") ";
		cin >> endPoints[i];
	}
	if(!(f.checkFieldPoints(endPoints)))
	{
		cout << "Invalid field points. Try again." << endl;
		return;
	}
	f = Field(endPoints, Ball());
	
	Ball ball;
	cin >> ball;
	if(!(f.checkBallCenter(ball)))
	{
		cout << "Invalid ball center. Try again." << endl;
		return;
	}
	if(!(f.checkBallDiameter(ball)))
	{
		cout << "Invalid ball diameter. Try again." << endl;
		return;
	}
	f.ball = ball;
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
