#include "Attractor.h"

Attractor::Attractor()
	: WorldObject()
	, mAttractionFactor(0.0f)
{
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	mCollisionRadius = 10.0f;
	mMass = 10000000.0f;
	SetupVisual();
}

Attractor::Attractor(float attractionFactor)
	: WorldObject()
	, mAttractionFactor(attractionFactor)
{
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	mCollisionRadius = 10.0f * attractionFactor;
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

void Attractor::OnCollision(WorldObject * collidingObject)
{
	collidingObject->Kill();
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

void Attractor::UpdatePhysics(const float deltaTime)
{
	WorldObject::UpdatePhysics(deltaTime);
}

void Attractor::Draw(sf::RenderWindow* drawWindow)
{
	WorldObject::Draw(drawWindow);
	// extra visual effects
}

sf::Shape* Attractor::GenerateModel() const
{	
	sf::CircleShape* attractorShape = new sf::CircleShape(mCollisionRadius, 30);
	attractorShape->setOrigin(mCollisionRadius, mCollisionRadius);
	attractorShape->setFillColor(sf::Color::Black);
	attractorShape->setOutlineThickness(-1.5f); 
	attractorShape->setOutlineColor(sf::Color::White);
	return attractorShape;
}
