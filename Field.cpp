#include "Vector.h"
#include "Line.h"
#include "Field.h"

Field::Field() {}
Field::Field(const Point& origin, double width, double height, const Ball& ball) : ball(ball), startingPoint(ball.center), width(width), height(height)
{
	endPoints[0] = Point(origin.x, origin.y);
	endPoints[1] = Point(origin.x + width, origin.y);
	endPoints[2] = Point(origin.x + width, origin.y + height);
	endPoints[3] = Point(origin.x, origin.y + height);
}
Field::Field(Point(& endPoints)[POINTS], const Ball& ball) : ball(ball), startingPoint(ball.center)
{
	for (int i = 0; i < POINTS; ++i)
	{
		this->endPoints[i] = endPoints[i];
	}
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
	
	Line AB(endPoints[0], endPoints[1]);
	Line BC(endPoints[1], endPoints[2]);
	Line CD(endPoints[2], endPoints[3]);
	Line DA(endPoints[3], endPoints[0]);
	double radius = ball.radius();
	double wratio = abs(DA.C - BC.C) / width;
	double hratio = abs(CD.C - AB.C) / height;
	DA.C -= radius * wratio; BC.C -= radius * wratio;
	CD.C -= radius * hratio; AB.C -= radius * hratio;
	bool someOtherFlag = 1;
	Vector trajectory = Vector(ball.center.x, ball.center.y) + Vector(ball.center, target) * power;
	
	bool flag = 1;
	while(flag)
	{
		Line TR(ball.center, Point(trajectory.x, trajectory.y));
		for(int i = 0; i < POINTS; ++i)
		{
			TR.substitute(Vector(endPoints[i].x, endPoints[i].y));
			if((TR.sub < 0.001) && (TR.sub >= 0))
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
					DA.C += radius * wratio; BC.C += radius * wratio;
					CD.C += radius * hratio; AB.C += radius * hratio;
					someOtherFlag = 0;
				}
				break;
			}
		}
		
		AB.substitute(trajectory);
		BC.substitute(trajectory);
		CD.substitute(trajectory);
		DA.substitute(trajectory);
		
		Line* min = &AB;
		if(BC.sub < min->sub) min = &BC;
		if(CD.sub < min->sub) min = &CD;
		if(DA.sub < min->sub) min = &DA;
		if(min->sub < 0)
		{
			Line l(min->A, min->B, min->C - (-(min->sub)));
			if(min == &AB)
			{
				ball.center = Point(min->solve(TR).x, min->solve(TR).y);
				cout << "The ball bounced into the wall AB at " << ball.center << endl;
				trajectory = l.solve(Line(BC.A, BC.B, BC.C - BC.sub));
				continue;
			}
			if(min == &BC)
			{
				ball.center = Point(min->solve(TR).x, min->solve(TR).y);
				cout << "The ball bounced into the wall BC at " << ball.center << endl;
				trajectory = l.solve(Line(CD.A, CD.B, CD.C - CD.sub));
				continue;
			}
			if(min == &CD)
			{
				ball.center = Point(min->solve(TR).x, min->solve(TR).y);
				cout << "The ball bounced into the wall CD at " << ball.center << endl;
				trajectory = l.solve(Line(DA.A, DA.B, DA.C - DA.sub));
				continue;
			}
			if(min == &DA)
			{
				ball.center = Point(min->solve(TR).x, min->solve(TR).y);
				cout << "The ball bounced into the wall DA at " << ball.center << endl;
				trajectory = l.solve(Line(AB.A, AB.B, AB.C - AB.sub));
				continue;
			}
		}
		
		flag = 0;
	}
	ball.center = Point(trajectory.x, trajectory.y);
}

bool Field::checkBall(const Ball& ball)
{
	return (bool)(ball.diameter >= 0);
}
bool Field::checkWidthHeight(double width, double height)
{
	return (bool)(((width / height) == 2) || ((width / height) == 0.5));
}
bool Field::checkEndPoints(Point(& endPoints)[POINTS])
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
	Point endPoints[POINTS];
	cout << "Field points: " << endl;
	for (int i = 0; i < POINTS; ++i)
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
	for(int i = 0; i < POINTS; ++i)
	{
		out << "  " << f.endPoints[i] << endl;
	}
	out << f.ball;
	
	return out;
}
