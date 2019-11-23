#pragma once
#include "WorldObject.h"

class Bullet : public WorldObject
{
public:
	Bullet();

	virtual void OnCollision(WorldObject* collidingObject) override;
protected:

	virtual void UpdatePhysics(const float deltaTime) override;

	// Drawable Implementation
public:
	virtual void Draw(sf::RenderWindow* drawWindow) override;
protected:
	virtual sf::Shape* GenerateModel() const override;
	virtual void UpdateVisual() override;

	// movement trail
	int mMaxNumTrailVertices = 30;
	std::vector<sf::Vertex> mTrail;
};