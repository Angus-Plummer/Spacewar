#pragma once
#include "WorldObject.h"

class Bullet : public WorldObject
{
public:
	Bullet();

	virtual void Update(const float deltaTime) override;

	virtual void Kill() override;

	virtual void OnCollision(WorldObject* collidingObject) override;
protected:

	virtual void UpdatePhysics(const float deltaTime) override;

	virtual void OnLeaveWorldBounds();

	// Drawable Implementation
public:
	virtual void Draw(sf::RenderWindow* drawWindow) override;
protected:
	virtual sf::Shape* GenerateModel() const override;
	virtual void UpdateVisual(const float deltaTime) override;

	// movement trail
	int mMaxNumTrailVertices = 20;
	std::vector<std::vector<sf::Vertex>> mTrail; // vector of vectors as they can be discontinuous due to wrapping
};