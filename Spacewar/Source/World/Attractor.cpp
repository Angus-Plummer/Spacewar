#include "Attractor.h"

Attractor::Attractor()
	: WorldObject()
	, mAttractionFactor(0.0f)
	, mDeathDistance(0.0f)
{
	mMass = 10000000.0f;
	SetupVisual();
}

Attractor::Attractor(float attractionFactor, float deathDistance)
	: WorldObject()
	, mAttractionFactor(attractionFactor)
	, mDeathDistance(deathDistance)
{
	mMass = 1000000.0f;
	SetupVisual();
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

void Attractor::ApplyForce(WorldObject* otherObject)
{
	// one way, only apply force to target
	Vector2D deltaPos = otherObject->GetPosition() - mPosition;
	Vector2D curVel = otherObject->GetVelocity();
	float distance = deltaPos.Magnitude();
	float otherMass = otherObject->GetMass();

	float forceMag = -(mAttractionFactor * mMass * otherMass / (distance * distance));
	Vector2D force = deltaPos.Normalised() * forceMag;

	otherObject->AddForce(force);
}

void Attractor::Draw(sf::RenderWindow* drawWindow)
{
	WorldObject::Draw(drawWindow);
	// extra visual effects
}

sf::Shape* Attractor::GenerateModel() const
{	
	sf::CircleShape* attractorShape = new sf::CircleShape(mDeathDistance, 30);
	// create spaceship shape and assign to drawn shape
	attractorShape->setFillColor(sf::Color::White);
	//attractorShape->setOutlineThickness(-1.0f); // outline from edge towards centre
	//attractorShape->setOutlineColor(sf::Color(255, 255, 255));
	attractorShape->setOrigin(mDeathDistance / 2.0f, mDeathDistance / 2.0f);
	return attractorShape;
}
