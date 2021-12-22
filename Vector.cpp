#include "Vector.h"

Vector::Vector() : Point(0, 0) {}
Vector::Vector(double x, double y) : Point(x, y) {}
Vector::Vector(const Point& p1, const Point& p2) : Point(p2.x - p1.x, p2.y - p1.y) {}

Vector Vector::operator+(const Vector& other)
{
	return Vector(x + other.x, y + other.y);
}
Vector Vector::operator*(double scalar)
{
	return Vector(x * scalar, y * scalar);
}
