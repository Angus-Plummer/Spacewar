#pragma once
#include "WorldObject.h"

class SpaceShip : public WorldObject
{
public:
	SpaceShip();

	void Kill();
	bool IsAlive();

	// TODO: various functions for movement + firing

protected:
	int mAmmo;
	float mHealth;
	bool mIsAlive;

	virtual void SetupShape() override;

	virtual void UpdatePhysics(const float deltaTime) override;
};