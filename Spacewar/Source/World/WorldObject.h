#pragma once
#include "../Math/Vector2D.h"
#include "../Drawable.h"

// class for game objects which exist physically in the world
class WorldObject : public Drawable
{
public:
	WorldObject();
	~WorldObject();

	virtual void Update(const float deltaTime);

	void SetPosition(const Vector2D& newPos);
	Vector2D GetPosition() const;

	void SetVelocity(const Vector2D& newVel);
	Vector2D GetVelocity() const;

	void SetMass(float newMass);
	float GetMass() const;

	void AddForce(const Vector2D& force);

	void SetRotation(float newRot);
	float GetRotation() const;

	void SetIsPhysicsEnabled(bool isEnablePhysics);
	bool GetIsPhysicsEnabled() const;

protected:
	bool mIsPhysicsEnabled;
	float mMass;
	Vector2D mPosition;
	Vector2D mVelocity;
	Vector2D mPendingForce;

	float mRotation;
	// float mAngularVelocity;

	virtual void UpdatePhysics(const float deltaTime);

	// Drawable Implementation. Uses just one shape for primary object shape
public:
	virtual void Draw(sf::RenderWindow* drawWindow) override;
protected:
	sf::Shape* mModel; // main visual components
	virtual void UpdateVisual();
	virtual void SetupVisual();
	virtual sf::Shape* GenerateModel() const = 0; // generate model, can include randomness
};