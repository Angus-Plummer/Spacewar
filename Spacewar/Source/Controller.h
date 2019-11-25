#pragma once
#include "Input/InputAction.h"
#include "Input/KeyEventType.h"
#include "SFML/Window/Keyboard.hpp"

class SpaceShip;

class Controller
{
public:
	Controller(int id);

	virtual void Initialise();

	virtual void ProcessInputAction(InputAction action, KeyEventType keyEvent) = 0;

protected:
	int mId;

	void RegisterInputBinding(InputAction action, sf::Keyboard::Key key);

	virtual void SetupInput();
};