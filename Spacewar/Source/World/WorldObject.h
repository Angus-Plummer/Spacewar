#pragma once
#include "../Math/Vector2D.h"
#include "../Drawable.h"

class World;

// class for game objects which exist physically in the world
class WorldObject : public Drawable
{
public:
	WorldObject();
	~WorldObject();

	virtual void Update(const float deltaTime);

	void SetWorld(World* world);

	virtual void Kill();
	bool IsAlive();

	Vector2D ForwardVector() const;

	void SetPosition(const Vector2D& newPos);
	Vector2D GetPosition() const;

	void SetVelocity(const Vector2D& newVel);
	Vector2D GetVelocity() const;

	void SetMass(float newMass);
	float GetMass() const;

	void AddForce(const Vector2D& force);

	void SetRotation(float newRot);
	float GetRotation() const;

	void SetAngularVelocity(float newAngularVel);
	float GetAngularVelocity() const;

	void SetIsPhysicsEnabled(bool isEnablePhysics);
	bool GetIsPhysicsEnabled() const;

	void SetIsCollisionEnabled(bool isCollisionEnabled);
	bool GetIsCollisionEnabled() const;

	void SetCollisionRadius(float radius);
	float GetCollisionRadius() const;

	void SetIsFaceMovementDirection(bool isFaceMoveDirection);
	bool GetIsFaceMovementDirection() const;

	virtual void OnCollision(WorldObject* collidingObject);

protected:
	World* mWorld;
	bool mIsPhysicsEnabled;
	bool mIsCollisionEnabled;
	bool mIsAlive;
	float mCollisionRadius;
	float mMass;
	Vector2D mPosition;
	Vector2D mVelocity;
	Vector2D mPendingForce;
	bool mIsWrapAround;

	float mRotation;
	float mAngularVelocity;
	bool mIsFaceMovementDirection;

	virtual void OnLeaveWorldBounds();

	virtual void UpdatePhysics(const float deltaTime);

	// Drawable Implementation. Uses just one shape for primary object shape
public:
	virtual void Draw(sf::RenderWindow* drawWindow) override;
protected:
	sf::Shape* mModel; // main visual components
	sf::FloatRect mCollisionRect;
	virtual void UpdateVisual();
	virtual void SetupVisual();
	virtual sf::Shape* GenerateModel() const = 0; // generate model, can include randomness
};