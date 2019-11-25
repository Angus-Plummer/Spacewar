#include "Debris.h"

Debris::Debris()
	: WorldObject()
	, mSize(2.0f)
{
	mCollisionRadius = mSize;
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	mIsWrapAround = false;
	SetupVisual();
}

Debris::Debris(float size)
	: WorldObject()
	, mSize(size)
{
	mCollisionRadius = mSize;
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	mIsWrapAround = false;
	SetupVisual();
}

void Debris::Kill()
{
	Destroy();
}

void Debris::OnCollision(WorldObject* collidingObject)
{
	Kill(); // kill self
}

void Debris::UpdatePhysics(const float deltaTime)
{
	WorldObject::UpdatePhysics(deltaTime);

}

sf::Shape * Debris::GenerateModel() const
{
	int numSides = 4 + rand() % 3;
	sf::CircleShape* debrisModel = new sf::CircleShape(mSize, numSides);

	// set origin 
	sf::Vector2f centre(mSize, mSize);
	debrisModel->setOrigin(centre);

	debrisModel->setFillColor(sf::Color::Transparent);
	debrisModel->setOutlineThickness(1.0f);
	debrisModel->setOutlineColor(sf::Color::White);//sf::Color(255, 50 + rand() % 150, 0));

	return debrisModel;
}
