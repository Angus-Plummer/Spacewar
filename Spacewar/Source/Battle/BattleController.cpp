#include "BattleController.h"
#include "SpaceShip.h"
#include "../Input/KeyEventType.h"

static const std::map<InputAction, sf::Keyboard::Key> kPlayer1Bindings =
{
	{InputAction::PowerThrusters, sf::Keyboard::W},
	{InputAction::RotateClockwise, sf::Keyboard::D},
	{InputAction::RotateAntiClockwise, sf::Keyboard::A},
	{InputAction::FireWeapon, sf::Keyboard::Space}
};

static const std::map<InputAction, sf::Keyboard::Key> kPlayer2Bindings =
{
	{InputAction::PowerThrusters, sf::Keyboard::Up},
	{InputAction::RotateClockwise, sf::Keyboard::Right},
	{InputAction::RotateAntiClockwise, sf::Keyboard::Left},
	{InputAction::FireWeapon, sf::Keyboard::Enter}
};

const std::map<int, std::map<InputAction, sf::Keyboard::Key>> BattleController::kBattleKeyBindings =
{
	{0, kPlayer1Bindings},
	{1, kPlayer2Bindings}
};

BattleController::BattleController(int id)
	: Controller(id)
	, mShip(nullptr)
{
}

void BattleController::ProcessInputAction(InputAction action, KeyEventType keyEvent)
{
	// find member input function pointer in map of maps for input
	auto findActionIter = mBattleActionMappings.find(action);
	if (findActionIter != mBattleActionMappings.end())
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

bool BattleController::GetKeyForAction(InputAction action, sf::Keyboard::Key& key) const
{
	// if base class found no key binding then check the battle keys
	bool bIsKeyFound = Controller::GetKeyForAction(action, key);
	if (!bIsKeyFound)
	{
		// find key in battle key bindings map
		auto findPlayerMappingsIter = kBattleKeyBindings.find(mId);
		if (findPlayerMappingsIter != kBattleKeyBindings.end())
		{
			const std::map<InputAction, sf::Keyboard::Key> playerInputBindings = findPlayerMappingsIter->second;
			auto findKeyIter = playerInputBindings.find(action);
			if (findKeyIter != playerInputBindings.end())
			{
				key = findKeyIter->second;
				bIsKeyFound = true;
			}
		}
	}
	return bIsKeyFound;
}

void BattleController::SetupInput()
{
	CreateInputBinding(InputAction::PowerThrusters, KeyEventType::KeyDown, &BattleController::EnableShipThrusters);
	CreateInputBinding(InputAction::PowerThrusters, KeyEventType::KeyUp, &BattleController::DisableShipThrusters);

	CreateInputBinding(InputAction::RotateClockwise, KeyEventType::KeyDown, &BattleController::StartShipClockwiseRotation);
	CreateInputBinding(InputAction::RotateClockwise, KeyEventType::KeyUp, &BattleController::StopShipClockwiseRotation);

	CreateInputBinding(InputAction::RotateAntiClockwise, KeyEventType::KeyDown, &BattleController::StartShipAntiClockwiseRotation);
	CreateInputBinding(InputAction::RotateAntiClockwise, KeyEventType::KeyUp, &BattleController::StopShipAntiClockwiseRotation);

	CreateInputBinding(InputAction::FireWeapon, KeyEventType::KeyDown, &BattleController::FireShipWeapon);
}

bool BattleController::CreateInputBinding(InputAction action, KeyEventType eventType, BattleInputFunction boundFunction)
{
	sf::Keyboard::Key key;
	bool foundKey = GetKeyForAction(action, key);
	if (foundKey)
	{
		// add mapping to the action mapping map
		std::map<KeyEventType, BattleInputFunction>& actionMapping = mBattleActionMappings[action];
		BattleInputFunction& function = actionMapping[eventType];
		function = boundFunction;

		// register with the input manager
		RegisterInputBinding(action, key);
	}
	return foundKey;
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
