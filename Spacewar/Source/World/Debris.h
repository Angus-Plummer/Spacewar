#pragma once
#include "WorldObject.h"

class Debris : public WorldObject
{
public:
	Debris();
	Debris(float size);

	virtual void OnCollision(WorldObject* collidingObject) override;

	// Drawable Implementation
protected:
	float mSize; // characteristic length scale
	virtual sf::Shape* GenerateModel() const override;
};