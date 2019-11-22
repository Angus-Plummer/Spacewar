#pragma once
#include <SFML/Graphics.hpp>
#include "../Math/Vector2D.h"

// class for game objects which are drawn on the screen
class WorldObject
{
public:
	WorldObject();
	~WorldObject();

	virtual void Update(const float deltaTime);

	void SetPosition(const Vector2D& newPos);
	Vector2D GetPosition() const;

	void SetVelocity(const Vector2D& newVel);
	Vector2D GetVelocity() const;

	void AddForce(const Vector2D& force);

	void SetRotation(float newRot);
	float GetRotation() const;

	void SetIsPhysicsEnabled(bool isEnablePhysics);
	bool GetIsPhysicsEnabled() const;

	const sf::Shape* GetShape() const;
	void Draw();

protected:
	bool mIsPhysicsEnabled;
	Vector2D mPosition;
	Vector2D mVelocity;
	Vector2D mPendingForce;

	float mRotation;
	// float mAngularVelocity;

	sf::Shape* mShape;
	virtual void SetupShape() = 0;

	virtual void UpdateShape();
	virtual void UpdatePhysics(const float deltaTime);
};