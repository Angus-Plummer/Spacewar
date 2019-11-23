#pragma once
#include "../Controller.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

typedef void (Controller::*ControllerInputFunction)();

struct InputBinding
{
	Controller* BoundController = nullptr;
	sf::Keyboard::Key Key;
	ControllerInputFunction KeyPressFunction = nullptr;
	ControllerInputFunction KeyReleaseFunction = nullptr;
};