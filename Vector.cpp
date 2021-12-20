#include "Vector.h"

Vector Vector::operator+(const Vector& other)
{
	return Vector(x + other.x, y + other.y);
}
Vector Vector::operator*(double scalar)
{
	return Vector(x * scalar, y * scalar);
}
