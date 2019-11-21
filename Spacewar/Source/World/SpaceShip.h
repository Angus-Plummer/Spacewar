#pragma once
#include "WorldObject.h"

class SpaceShip : public WorldObject
{
public:
	SpaceShip();


	// TODO: various functions for movement + firing

protected:
	int mAmmo;
	float mHealth;

	virtual void SetupShape() override;

	virtual void UpdatePhysics(const float deltaTime) override;
};