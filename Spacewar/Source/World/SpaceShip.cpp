#include "SpaceShip.h"

SpaceShip::SpaceShip() 
	: WorldObject()
	, mAmmo(0)
	, mHealth(0.0f)
{
	// create spaceship shape and assign to drawn shape
	mShape = new sf::CircleShape(15.f);
	mShape->setFillColor(sf::Color::Black);
	mShape->setOutlineThickness(-1.0f); // outline from edge towards centre
	mShape->setOutlineColor(sf::Color(255, 255, 255));
}
