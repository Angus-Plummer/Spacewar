#pragma once
#include "InputBinding.h"
#include <SFML/Window/Event.hpp>
#include <map>

class InputManager
{
public:
	void AddBinding(Controller* controller, sf::Keyboard::Key key, InputAction boundFunction);
	void ProcessInput(sf::Keyboard::Key key, sf::Event::EventType eventType);
protected:
	std::map<sf::Keyboard::Key, InputBinding> mInputBindings;
};