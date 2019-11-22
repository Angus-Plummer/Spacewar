#include "Debris.h"

Debris::Debris()
	: WorldObject()
	, mSize(2.0f)
{
	mIsPhysicsEnabled = true;
	SetupVisual();
}

Debris::Debris(float size)
	: WorldObject()
	, mSize(size)
{
	mIsPhysicsEnabled = true;
	SetupVisual();
}

sf::Shape * Debris::GenerateModel() const
{
	int numSides = 3 + rand() % 3;
	sf::CircleShape* debrisModel = new sf::CircleShape(mSize, numSides);

	// set origin 
	sf::Vector2f centre(mSize / 2.0f, mSize / 2.0f);
	debrisModel->setOrigin(centre);

	debrisModel->setFillColor(sf::Color::White);
	debrisModel->setOutlineThickness(-1.0f); // outline from edge towards centre
	debrisModel->setOutlineColor(sf::Color(255, 255, 255));

	return debrisModel;
}
