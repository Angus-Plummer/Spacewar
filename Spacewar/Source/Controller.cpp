#include "Controller.h"

Controller::Controller() : mShip(nullptr)
{
}

void Controller::SetShip(SpaceShip* newShip)
{
	mShip = newShip;
}

SpaceShip * Controller::GetShip() const
{
	return mShip;
}
