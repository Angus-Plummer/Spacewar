#pragma once
#include <SFML/Graphics.hpp>
#include "../Math/Vector2D.h"

// class for game objects which are drawn on the screen
class WorldObject
{
public:
	WorldObject();
	~WorldObject();

	void Update(const float deltaTime);

	void SetPosition(const Vector2D& newPos);
	Vector2D GetPosition() const;

	void SetVelocity(const Vector2D& newVel);
	Vector2D GetVelocity() const;

	void SetRotation(float newRot);
	float GetRotation() const;

	const sf::Shape* GetShape() const;

protected:
	Vector2D mPosition;
	Vector2D mVelocity;

	float mRotation;
	// float mAngularVelocity;

	sf::Shape* mShape;

	void UpdateShape();
};