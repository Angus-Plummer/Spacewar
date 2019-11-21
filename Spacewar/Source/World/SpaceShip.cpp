#include "SpaceShip.h"

SpaceShip::SpaceShip() 
	: WorldObject()
	, mAmmo(0)
	, mHealth(0.0f)
{
	mIsPhysicsEnabled = true;
	SetupShape();
}

void SpaceShip::SetupShape()
{
	// create spaceship shape and assign to drawn shape
	float radius = 10.0f;
	mShape = new sf::CircleShape(radius, 3); // eq. triangle
	mShape->setFillColor(sf::Color::Black);
	mShape->setOutlineThickness(-1.0f); // outline from edge towards centre
	mShape->setOutlineColor(sf::Color(255, 255, 255));
	mShape->setOrigin(radius / 2.0f, radius / 2.0f);
}

void SpaceShip::UpdatePhysics(const float deltaTime)
{
	WorldObject::UpdatePhysics(deltaTime);
	float radians = atan2(mVelocity.Y, mVelocity.X);
	float degrees = radians * (180.0 / 3.141592653589793238463);
	mRotation = degrees + 90.0f; // point is at -90deg so do extra rot
}
