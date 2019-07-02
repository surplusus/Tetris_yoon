#include "Vector2.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

const Vector2 Vector2::zeroPoint = Vector2(0, 0);
const Vector2 Vector2::oneByOne = Vector2(1, 1);

const Vector2 operator*(float scalar, const Vector2 & vec)
{
	return vec.operator*(scalar);
}

std::istream & operator>>(std::istream & is, Vector2 & vec)
{
	is >> vec.x >> vec.y;
	return is;
}

const Vector2 Vector2::Normalize(float _x, float _y) const
{
	if (_x != 0 && _y != 0)
	{
		Vector2 tmp(this->x - _x, this->y - _y);
		return Vector2(tmp.x / tmp.Magnitude(), tmp.y / tmp.Magnitude());
	}
	else
		return Vector2(this->x / Magnitude(), this->y / Magnitude());
}

float Vector2::Magnitude() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

float Vector2::DistTwoDot(const Vector2 & vec1, const Vector2 & vec2)
{
	return sqrt((vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y)*(vec1.y - vec2.y));
}

float Vector2::DotProduct(const Vector2 & vec1, const Vector2 & vec2)
{
	return vec1.x*vec2.x + vec1.y*vec2.y;
}

const Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x*scalar, y*scalar);
}

const Vector2 Vector2::operator+(const Vector2 & vec)
{
	return Vector2(x + vec.x, y + vec.y);
}

const Vector2 Vector2::operator-(const Vector2 & vec)
{
	return Vector2(x - vec.x, y - vec.y);
}

Vector2 & Vector2::operator*=(float scalar)
{
	x *= scalar;	y *= scalar;
	return *this;
}

Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	x += vec.x;		y += vec.y;
	return *this;
}
