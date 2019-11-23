#pragma once
#include "WorldObject.h"

class Debris;

class SpaceShip : public WorldObject
{
public:
	SpaceShip();

	virtual void Update(const float deltaTime) override;

	// TODO: various functions for movement + firing

	void FireBullet();
	void EnableThrusters();
	void DisableThrusters();

	virtual void OnCollision(WorldObject* collidingObject) override;

	virtual void Kill() override;

	// explosion
	void GenerateDebris(int numPieces) const;

protected:
	bool mIsThrustersEnabled;
	float mFuel;
	int mAmmo;
	float mHealth;

	virtual void UpdatePhysics(const float deltaTime) override;

	// Drawable Implementation
public:
	virtual void Draw(sf::RenderWindow* drawWindow) override;
protected:
	float mShipWidth;
	float mShipLength;
	virtual sf::Shape* GenerateModel() const override;
	virtual void UpdateVisual() override;

	// thrusters
	std::vector<sf::Shape*> mThrustersModel;
	std::vector<sf::Shape*> GenerateThrustersModel();
	virtual void SetupVisual();

	// movement trail
	int mMaxNumTrailVertices = 30;
	std::vector<sf::Vertex> mTrail;
};