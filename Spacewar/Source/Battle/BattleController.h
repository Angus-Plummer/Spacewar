#pragma once
#include "../Controller.h"
#include <map>

class BattleController; 
typedef void (BattleController::*BattleInputFunction)();

class BattleController : public Controller
{
public:
	BattleController(int id);

	virtual void ProcessInputAction(InputAction action, KeyEventType keyEvent) override;

	void SetShip(SpaceShip* newShip);
	SpaceShip* GetShip() const;
protected:
	virtual void SetupInput();
	virtual void CreateInputBinding(InputAction action, sf::Keyboard::Key key, KeyEventType eventType, BattleInputFunction boundFunction);
	std::map<InputAction, std::map<KeyEventType, BattleInputFunction>> mActionMappings;

	SpaceShip* mShip;

	void EnableShipThrusters();
	void DisableShipThrusters();

	void StartShipClockwiseRotation();
	void StopShipClockwiseRotation();

	void StartShipAntiClockwiseRotation();
	void StopShipAntiClockwiseRotation();

	void FireShipWeapon();

};

