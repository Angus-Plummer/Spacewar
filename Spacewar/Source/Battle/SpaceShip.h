#pragma once
#include "WorldObject.h"

class Debris;

enum TurningDirection
{
	Clockwise,
	AntiClockwise
};

class SpaceShip : public WorldObject
{
public:
	SpaceShip();

	virtual void Update(const float deltaTime) override;

	void FireBullet();
	void EnableThrusters();
	void DisableThrusters();

	void StartManualRotation(TurningDirection direction);
	void StopManualRotation(TurningDirection direction);

	virtual void OnCollision(WorldObject* collidingObject) override;

	virtual void Kill() override;

	// explosion
	void GenerateDebris(int numPieces) const;

protected:
	bool mIsThrustersEnabled;
	float mFuel;
	int mAmmo;
	float mHealth;
	float mManualRotationRate;
	float mThrusterImpulse;

	void FireThrusters(const float deltaTime);

	virtual void UpdatePhysics(const float deltaTime) override;

	// Drawable Implementation
public:
	virtual void Draw(sf::RenderWindow* drawWindow) override;
protected:
	float mShipWidth;
	float mShipLength;
	virtual sf::Shape* GenerateModel() const override;
	virtual void UpdateVisual(const float deltaTime) override;

	// thrusters
	std::vector<sf::Shape*> mThrustersModel;
	std::vector<sf::Shape*> GenerateThrustersModel();
	virtual void SetupVisual();

	// movement trail
	int mMaxNumTrailVertices = 30;
	std::vector<sf::Vertex> mTrail;
};