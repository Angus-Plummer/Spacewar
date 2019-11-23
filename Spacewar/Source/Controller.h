#pragma once

class SpaceShip;

class Controller
{
public:
	Controller();

	void Initialise();

	void SetShip(SpaceShip* newShip);
	SpaceShip* GetShip() const;
protected:
	SpaceShip* mShip;

	void SetupInput();

	void EnableShipThrusters();
	void DisableShipThrusters();

	void StartShipClockwiseRotation();
	void StopShipClockwiseRotation();

	void StartShipAntiClockwiseRotation();
	void StopShipAntiClockwiseRotation();

	void FireShipWeapon();

};