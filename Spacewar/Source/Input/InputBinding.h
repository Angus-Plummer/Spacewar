#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "InputAction.h"

class Controller;

struct InputBinding
{
	sf::Keyboard::Key Key;
	Controller* Controller = nullptr;
	InputAction Action;
};