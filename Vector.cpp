#include "Vector.h"

Vector::Vector(double x, double y) : Point(x, y) {}
Vector::Vector(const Point& p) : Point(p) {}
Vector::Vector(const Point& p1, const Point& p2) : Point(p1, p2) {}
Vector::Vector() : Point(0, 0) {}

Vector& Vector::operator+=(const Vector& other)
{
	x += other.x;
	y += other.y;
	return *this;
}
Vector Vector::operator*(double scalar) const
{
	return Vector(x * scalar, y * scalar);
}
