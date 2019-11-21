#pragma once
#include "World/SpaceShip.h"

class Controller
{
public:
	Controller();

	void SetShip(SpaceShip* newShip);
	SpaceShip* GetShip() const;
protected:
	SpaceShip* mShip;
};