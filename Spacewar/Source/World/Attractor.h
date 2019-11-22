#pragma once
#include "WorldObject.h"

class Attractor : public WorldObject
{
public:
	Attractor();
	Attractor(float attractionFactor);

	void SetAttractionFactor(float newAttractionFactor);
	float GetAttractionFactor() const;

	void ApplyForce(WorldObject* otherObject);

protected:
	float mAttractionFactor;

	virtual void UpdatePhysics(const float deltaTime) override;

	// Drawable Implementation
public:
	virtual void Draw(sf::RenderWindow* drawWindow) override;
protected:
	virtual sf::Shape* GenerateModel() const override;

};