#include "BattleController.h"
#include "SpaceShip.h"
#include "../Input/KeyEventType.h"

BattleController::BattleController(int id)
	: Controller(id)
	, mShip(nullptr)
{
}

void BattleController::ProcessInputAction(InputAction action, KeyEventType keyEvent)
{
	auto findActionIter = mActionMappings.find(action);
	if (findActionIter != mActionMappings.end())
	{
		std::map<KeyEventType, BattleInputFunction>& actionMapping = findActionIter->second;
		auto findEventIter = actionMapping.find(keyEvent);
		if (findEventIter != actionMapping.end())
		{
			BattleInputFunction boundFunction = findEventIter->second;
			(this->*boundFunction)();
		}
	}
}

void BattleController::SetShip(SpaceShip * newShip)
{
	mShip = newShip;
	mShip->SetIsFaceMovementDirection(false);
}

SpaceShip * BattleController::GetShip() const
{
	return mShip;
}

void BattleController::SetupInput()
{
	CreateInputBinding(InputAction::PowerThrusters, sf::Keyboard::W, KeyEventType::KeyDown, &BattleController::EnableShipThrusters);
	CreateInputBinding(InputAction::PowerThrusters, sf::Keyboard::W, KeyEventType::KeyUp, &BattleController::DisableShipThrusters);

	CreateInputBinding(InputAction::RotateClockwise, sf::Keyboard::D, KeyEventType::KeyDown, &BattleController::StartShipClockwiseRotation);
	CreateInputBinding(InputAction::RotateClockwise, sf::Keyboard::D, KeyEventType::KeyUp, &BattleController::StopShipClockwiseRotation);

	CreateInputBinding(InputAction::RotateAntiClockwise, sf::Keyboard::A, KeyEventType::KeyDown, &BattleController::StartShipAntiClockwiseRotation);
	CreateInputBinding(InputAction::RotateAntiClockwise, sf::Keyboard::A, KeyEventType::KeyUp, &BattleController::StopShipAntiClockwiseRotation);

	CreateInputBinding(InputAction::FireWeapon, sf::Keyboard::Space, KeyEventType::KeyDown, &BattleController::FireShipWeapon);
}

void BattleController::CreateInputBinding(InputAction action, sf::Keyboard::Key key, KeyEventType eventType, BattleInputFunction boundFunction)
{
	// add mapping to the action mapping map
	std::map<KeyEventType, BattleInputFunction>& actionMapping = mActionMappings[action];
	BattleInputFunction& function = actionMapping[eventType];
	function = boundFunction;

	// register with the input manager
	RegisterInputBinding(action, key);
}

void BattleController::EnableShipThrusters()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->EnableThrusters();
	}
}

void BattleController::DisableShipThrusters()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->DisableThrusters();
	}
}

void BattleController::StartShipClockwiseRotation()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->StartManualRotation(TurningDirection::Clockwise);
	}
}

void BattleController::StopShipClockwiseRotation()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->StopManualRotation(TurningDirection::Clockwise);
	}
}

void BattleController::StartShipAntiClockwiseRotation()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->StartManualRotation(TurningDirection::AntiClockwise);
	}
}

void BattleController::StopShipAntiClockwiseRotation()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->StopManualRotation(TurningDirection::AntiClockwise);
	}
}

void BattleController::FireShipWeapon()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->FireBullet();
	}
}
