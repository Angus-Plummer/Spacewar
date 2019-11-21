#pragma once
#include "WorldObject.h"

class SpaceShip : public WorldObject
{
public:
	SpaceShip();

	// TODO: various functions for movement + firing

private:
	int mAmmo;
	float mHealth;
};