#pragma once
#include "WorldObject.h"

class Debris;

class SpaceShip : public WorldObject
{
public:
	SpaceShip();

	virtual void Update(const float deltaTime) override;

	// TODO: various functions for movement + firing

	virtual void OnCollision() override;

	// explosion
	std::vector<Debris*> GenerateDebris(int numPieces) const;

protected:
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

	// movement trail
	int mMaxNumTrailVertices = 30;
	std::vector<sf::Vertex> mTrail;
};