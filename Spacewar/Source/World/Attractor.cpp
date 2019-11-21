#include "Attractor.h"

Attractor::Attractor()
	: WorldObject()
	, mAttractionFactor(0.0f)
	, mDeathDistance(0.0f)
{
	SetupShape();
}

Attractor::Attractor(float attractionFactor, float deathDistance)
	: WorldObject()
	, mAttractionFactor(attractionFactor)
	, mDeathDistance(deathDistance)
{
	SetupShape();
}

void Attractor::SetAttractionFactor(float newAttractionFactor)
{
	mAttractionFactor = newAttractionFactor;
}

float Attractor::GetAttractionFactor() const
{
	return mAttractionFactor;
}

void Attractor::SetDeathDistance(float deathDistance)
{
	mDeathDistance = deathDistance;
}

float Attractor::GetDeathDistance() const
{
	return mDeathDistance;
}

void Attractor::ApplyForce(WorldObject* otherObject, const float deltaTime)
{
	// one way, only apply force to target
	Vector2D deltaPos = otherObject->GetPosition() - mPosition;
	Vector2D curVel = otherObject->GetVelocity();
	float distance = deltaPos.Magnitude();

	float accelerationMag = -(mAttractionFactor / (distance * distance));
	Vector2D acceleration = deltaPos.Normalised() * accelerationMag;

	Vector2D newVel = curVel + (acceleration * deltaTime);
	otherObject->SetVelocity(newVel);
}

void Attractor::SetupShape()
{
	// create spaceship shape and assign to drawn shape
	mShape = new sf::CircleShape(mDeathDistance, 30);
	mShape->setFillColor(sf::Color::White);
	mShape->setOutlineThickness(-1.0f); // outline from edge towards centre
	mShape->setOutlineColor(sf::Color(255, 255, 255));
	mShape->setOrigin(mDeathDistance /2.0f, mDeathDistance /2.0f);
}
