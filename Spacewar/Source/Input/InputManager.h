#pragma once
#include "InputBinding.h"
#include <map>

class InputManager
{
public:
	void AddBinding(Controller* controller, sf::Keyboard::Key key, sf::Event::EventType eventType, ControllerInputFunction boundFunction);

	void ProcessInput(sf::Keyboard::Key key, sf::Event::EventType eventType);
protected:
	std::map<sf::Keyboard::Key, InputBinding> mInputBindings;
};