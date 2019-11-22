#pragma once
#include "WorldObject.h"

class SpaceShip : public WorldObject
{
public:
	SpaceShip();

	void Kill();
	bool IsAlive();

	virtual void Update(const float deltaTime) override;

	// TODO: various functions for movement + firing

protected:
	int mAmmo;
	float mHealth;
	bool mIsAlive;

	virtual void UpdatePhysics(const float deltaTime) override;

	// Drawable Implementation
public:
	virtual void Draw(sf::RenderWindow* drawWindow) override;
protected:
	virtual sf::ConvexShape* GenerateModel() const override;
	virtual void UpdateVisual() override;

	// movement trail
	int mMaxNumTrailVertices = 30;
	std::vector<sf::Vertex> mTrail;

	// explosion
	std::vector<sf::Shape*> GenerateDebris();
};