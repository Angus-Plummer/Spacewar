#include "Debris.h"

Debris::Debris()
	: WorldObject()
	, mSize(2.0f)
{
	mCollisionRadius = mSize;
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	SetupVisual();
}

Debris::Debris(float size)
	: WorldObject()
	, mSize(size)
{
	mCollisionRadius = mSize;
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	SetupVisual();
}

void Debris::OnCollision()
{
	Kill();
}

sf::Shape * Debris::GenerateModel() const
{
	int numSides = 3 + rand() % 3;
	sf::CircleShape* debrisModel = new sf::CircleShape(mSize, numSides);

	// set origin 
	sf::Vector2f centre(mSize, mSize);
	debrisModel->setOrigin(centre);

	debrisModel->setFillColor(sf::Color::Transparent);
	debrisModel->setOutlineThickness(-1.0f);
	debrisModel->setOutlineColor(sf::Color::White);//sf::Color(255, 50 + rand() % 150, 0));

	return debrisModel;
}
