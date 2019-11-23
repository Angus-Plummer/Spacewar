#include "InputManager.h"

void InputManager::AddBinding(Controller * controller, sf::Keyboard::Key key, sf::Event::EventType eventType, ControllerInputFunction boundFunction)
{
	// overwrites any existing binding to this key
	InputBinding& inputBinding = mInputBindings[key];
	inputBinding.BoundController = controller;
	inputBinding.Key = key;
	switch (eventType)
	{
		case (sf::Event::KeyPressed):
		{
			inputBinding.KeyPressFunction = boundFunction;
			break;
		}
		case (sf::Event::KeyReleased):
		{
			inputBinding.KeyReleaseFunction = boundFunction;
			break;
		}
		default:
		{
			// error
			break;
		}
	}
}

void InputManager::ProcessInput(sf::Keyboard::Key key, sf::Event::EventType eventType)
{
	auto iter = mInputBindings.find(key);
	if (iter != mInputBindings.end())
	{
		InputBinding binding = iter->second;
		ControllerInputFunction boundFunction = nullptr;
		switch (eventType)
		{
			case (sf::Event::KeyPressed):
			{
				boundFunction = binding.KeyPressFunction;;
				break;
			}
			case (sf::Event::KeyReleased):
			{
				boundFunction = binding.KeyReleaseFunction;;
				break;
			}
			default:
			{
				// error
				break;
			}
		}
		if (boundFunction)
		{
			// call the function on the controller
			(binding.BoundController->*boundFunction)();
		}
	}
}
