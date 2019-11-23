#include "Controller.h"
#include "GameInstance.h"
#include "Input/InputManager.h"
#include "World/SpaceShip.h"

Controller::Controller() : mShip(nullptr)
{
}

void Controller::Initialise()
{
	SetupInput();
}

void Controller::SetShip(SpaceShip* newShip)
{
	mShip = newShip;
}

SpaceShip * Controller::GetShip() const
{
	return mShip;
}

void Controller::SetupInput()
{
	InputManager* inputManager = GameInstance::GetInputManager();
	inputManager->AddBinding(this, sf::Keyboard::W, sf::Event::KeyPressed, &Controller::EnableShipThrusters);
	inputManager->AddBinding(this, sf::Keyboard::W, sf::Event::KeyReleased, &Controller::DisableShipThrusters);

	inputManager->AddBinding(this, sf::Keyboard::D, sf::Event::KeyPressed, &Controller::StartShipClockwiseRotation);
	inputManager->AddBinding(this, sf::Keyboard::D, sf::Event::KeyReleased, &Controller::StopShipClockwiseRotation);

	inputManager->AddBinding(this, sf::Keyboard::A, sf::Event::KeyPressed, &Controller::StartShipAntiClockwiseRotation);
	inputManager->AddBinding(this, sf::Keyboard::A, sf::Event::KeyReleased, &Controller::StopShipAntiClockwiseRotation);

	inputManager->AddBinding(this, sf::Keyboard::Space, sf::Event::KeyReleased, &Controller::FireShipWeapon);
}

void Controller::EnableShipThrusters()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->EnableThrusters();
	}
}

void Controller::DisableShipThrusters()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->DisableThrusters();
	}
}

void Controller::StartShipClockwiseRotation()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->StartManualRotation(TurningDirection::Clockwise);
	}
}

void Controller::StopShipClockwiseRotation()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->StopManualRotation(TurningDirection::Clockwise);
	}
}

void Controller::StartShipAntiClockwiseRotation()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->StartManualRotation(TurningDirection::AntiClockwise);
	}
}

void Controller::StopShipAntiClockwiseRotation()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->StopManualRotation(TurningDirection::AntiClockwise);
	}
}

void Controller::FireShipWeapon()
{
	if (mShip && mShip->IsAlive())
	{
		mShip->FireBullet();
	}
}
