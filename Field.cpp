#include "Field.h"
#include "Line.h"
#include "Vector.h"
#include <cmath>

Field::Field(Point origin, double width, double height, Ball ball) : ball(ball), startingPoint(ball.center)
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
}

void Field::hit(Point target, double power)
{
	if((power < 1) || (power > 10))
	{
		cout << "Invalid power. Try again." << endl;
		return;
	}
	
	double width = sqrt(pow(endPoints[1].x - endPoints[0].x, 2) + pow(endPoints[1].y - endPoints[0].y, 2));
	double height = sqrt(pow(endPoints[0].x - endPoints[3].x, 2) + pow(endPoints[0].y - endPoints[3].y, 2));
	Line AB(endPoints[0], endPoints[1]);
	Line BC(endPoints[1], endPoints[2]);
	Line CD(endPoints[2], endPoints[3]);
	Line DA(endPoints[3], endPoints[0]);
	Vector trajectory = Vector(ball.center.x, ball.center.y) + Vector(ball.center, target) * power;
	
	short unsigned int flag = 1;
	while(flag)
	{
		double ABSub = AB.substitute(trajectory);
		ABSub += ((ABSub > 0) * ((ball.diameter / 2) * (AB.C / height))) - ((ABSub < 0) * ((ball.diameter / 2) * (AB.C / height)));
		double BCSub = BC.substitute(trajectory);
		BCSub += ((BCSub > 0) * ((ball.diameter / 2) * (AB.C / width))) - ((BCSub < 0) * ((ball.diameter / 2) * (AB.C / width)));
		double CDSub = CD.substitute(trajectory);
		CDSub += ((CDSub > 0) * ((ball.diameter / 2) * (AB.C / height))) - ((CDSub < 0) * ((ball.diameter / 2) * (AB.C / height)));
		double DASub = DA.substitute(trajectory);
		DASub += ((DASub > 0) * ((ball.diameter / 2) * (AB.C / width))) - ((DASub < 0) * ((ball.diameter / 2) * (AB.C / width)));
		pair<double, double> xy;
		
		cout << "AB " << ABSub << " BC " << BCSub << endl;
		cout << "CD " << CDSub << " DA " << DASub << endl;
		cout << "TR " << trajectory.x << " " << trajectory.y << endl << endl;
		
		if(ABSub < 0)
		{
			//cout << "The ball bounced into the wall AB." << endl;
			xy = AB.solve(BC, -ABSub, BCSub);
			cout << "XY " << xy.first << " " << xy.second << endl << endl;
			trajectory = Vector(xy.first, xy.second);
			continue;
		}
		if(BCSub < 0)
		{
			//cout << "The ball bounced into the wall BC." << endl;
			xy = BC.solve(CD, -BCSub, CDSub);
			cout << "XY " << xy.first << " " << xy.second << endl << endl;
			trajectory = Vector(xy.first, xy.second);
			continue;
		}
		if(CDSub < 0)
		{
			//cout << "The ball bounced into the wall CD." << endl;
			xy = CD.solve(DA, -CDSub, DASub);
			cout << "XY " << xy.first << " " << xy.second << endl << endl;
			trajectory = Vector(xy.first, xy.second);
			continue;
		}
		if(DASub < 0)
		{
			//cout << "The ball bounced into the wall DA." << endl;
			xy = DA.solve(AB, -DASub, ABSub);
			cout << "XY " << xy.first << " " << xy.second << endl << endl;
			trajectory = Vector(xy.first, xy.second);
			continue;
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
	/*if((width / height) != 2)
	{
		cout << "Invalid width and height. Try again." << endl;
		return;
	}*/
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
	/*if(((endPoints[2].x - endPoints[0].x) / (endPoints[2].y - endPoints[0].y)) != 0.5)
	{
		cout << "Invalid field points. Try again." << endl;
		return;
	}*/
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
