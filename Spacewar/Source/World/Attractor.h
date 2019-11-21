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

	void ApplyForce(WorldObject* otherObject, const float deltaTime);

protected:
	float mAttractionFactor;
	float mDeathDistance;

	virtual void SetupShape() override;

};