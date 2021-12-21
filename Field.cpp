#include "Field.h"
#include "Line.h"
#include "Vector.h"
#include <cmath>

Field::Field(Point origin, double width, double height, Ball ball) : ball(ball), startingPoint(ball.center), width(width), height(height)
{
	endPoints[0] = Point(origin.x, origin.y);
	endPoints[1] = Point(origin.x + width, origin.y);
	endPoints[2] = Point(origin.x + width, origin.y + height);
	endPoints[3] = Point(origin.x, origin.y + height);
}
Field::Field(Point endPoints[4], Ball ball) : ball(ball), startingPoint(ball.center)
{
	for (int i = 0; i < 4; ++i)
	{
		this->endPoints[i] = endPoints[i];
	}
	width = sqrt(pow(endPoints[1].x - endPoints[0].x, 2) + pow(endPoints[1].y - endPoints[0].y, 2));
	height = sqrt(pow(endPoints[0].x - endPoints[3].x, 2) + pow(endPoints[0].y - endPoints[3].y, 2));
}

void Field::hit(Point target, double power)
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
	double radius = ball.diameter / 2;
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
		for(int i = 0; i < 4; ++i)
		{
			TR.substitute(Vector(endPoints[i].x, endPoints[i].y);
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

void ballCase(Field& f)
{
	Ball ball;
	cin >> ball;
	f = Field(f.endPoints, ball);
}
void simpleCase(Field& f)
{
	Point origin;
	double width, height;
	Ball ball;
	cout << "Point of origin of field: ";
	cin >> origin;
	cout << "Width and height of field: ";
	cin >> width >> height;
	cin >> ball;
	f = Field(origin, width, height, ball);	
}
void complexCase(Field& f)
{
	Point endPoints[4];
	Ball ball;
	cout << "Field points: " << endl;
	for (int i = 0; i < 4; ++i)
	{
		cout << "  " << i + 1 << ") ";
		cin >> endPoints[i];
	}
	cin >> ball;
	f = Field(endPoints, ball);
}

ostream& operator<<(ostream& out, const Field& f)
{
	out << "Field points:" << endl;
	for(int i = 0; i < 4; ++i)
	{
		out << "  " << f.endPoints[i] << endl;
	}
	out << f.ball;
	
	return out;
}
