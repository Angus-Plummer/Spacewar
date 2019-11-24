#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D() : X(0.0f), Y(0.0f)
{

}

Vector2D::Vector2D(float x, float y) : X(x), Y(y)
{
}

float Vector2D::Magnitude() const
{
	float mag = sqrt(X*X + Y*Y);
	return mag;
}

void Vector2D::Normalise()
{
	float mag = Magnitude();
	if (mag == 0.0f)
	{
		// error
		return;
	}

	X /= mag;
	Y /= mag;
}

Vector2D Vector2D::Normalised() const
{
	Vector2D normalisedVector(X, Y);
	normalisedVector.Normalise();
	return normalisedVector;
}

float Vector2D::DotProd(const Vector2D & otherVec) const
{
	float result = X * otherVec.X + Y * otherVec.Y;
	return result;
}

Vector2D Vector2D::Rotated(float rotationAngle)
{
	Vector2D rotatedVector;
	double radAngle = rotationAngle * PI / 180.0;
	rotatedVector.X = (float)(X * cos(radAngle)	+ Y * sin(radAngle));
	rotatedVector.Y = (float)(-1.0 * X * sin(radAngle) + Y * cos(radAngle));
	return rotatedVector;
}

Vector2D& Vector2D::operator+=(const Vector2D & rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D & rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;
	return *this;
}

Vector2D& Vector2D::operator*=(const float scalar)
{
	X *= scalar;
	Y *= scalar;
	return *this;
}

Vector2D& Vector2D::operator/=(const float scalar)
{
	X /= scalar;
	Y /= scalar;
	return *this;
}

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.X + rhs.X, lhs.Y + rhs.Y);
}

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.X - rhs.X, lhs.Y - rhs.Y);
}

Vector2D operator*(const Vector2D& lhs, const float scalar)
{
	return Vector2D(lhs.X * scalar, lhs.Y * scalar);
}

Vector2D operator/(const Vector2D& lhs, const float scalar)
{
	return Vector2D(lhs.X / scalar, lhs.Y / scalar);
}

bool operator==(const Vector2D& lhs, const Vector2D& rhs)
{
	bool bIsEqual = (lhs.X == rhs.X && lhs.Y == rhs.Y);
	return bIsEqual;
}