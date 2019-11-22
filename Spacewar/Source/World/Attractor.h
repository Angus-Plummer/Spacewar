#pragma once
#include "WorldObject.h"

class Attractor : public WorldObject
{
public:
	Attractor();
	Attractor(float attractionFactor, float deathDistance);

	void SetAttractionFactor(float newAttractionFactor);
	float GetAttractionFactor() const;

	void SetDeathDistance(float deathDistance);
	float GetDeathDistance() const;

	void ApplyForce(WorldObject* otherObject);

protected:
	float mAttractionFactor;
	float mDeathDistance;

	// Drawable Implementation
public:
	virtual void Draw(sf::RenderWindow* drawWindow) override;
protected:
	virtual sf::Shape* GenerateModel() const override;

};