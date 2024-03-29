#pragma once

#define PI 3.141592653589793238463

class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);

	float X;
	float Y;

	float Magnitude() const;
	void Normalise();
	Vector2D Normalised() const;

	float DotProd(const Vector2D& otherVec) const;
	Vector2D Rotated(float rotationAngle);

	friend Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
	friend Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);
	Vector2D& operator+=(const Vector2D& rhs);
	Vector2D& operator-=(const Vector2D& rhs);

	friend Vector2D operator*(const Vector2D& lhs, const float scalar);
	Vector2D& operator*=(const float scalar);
	friend Vector2D operator/(const Vector2D& lhs, const float scalar);
	Vector2D& operator/=(const float scalar);

	friend bool operator==(const Vector2D& lhs, const Vector2D& rhs);
};