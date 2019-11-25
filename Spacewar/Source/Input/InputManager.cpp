#include "InputManager.h"
#include "KeyEventType.h"
#include "../Controller.h"

void InputManager::AddBinding(Controller* controller, sf::Keyboard::Key key, InputAction action)
{
	// overwrites any existing binding to this key
	InputBinding& inputBinding = mInputBindings[key];
	inputBinding.Controller = controller;
	inputBinding.Action = action;
	inputBinding.Key = key;
}

void InputManager::ProcessInput(sf::Keyboard::Key key, sf::Event::EventType eventType)
{
	auto iter = mInputBindings.find(key);
	if (iter != mInputBindings.end())
	{
		InputBinding binding = iter->second;
		KeyEventType keyEvent;

		switch (eventType)
		{
			case (sf::Event::KeyPressed):
			{
				keyEvent = KeyDown;
				break;
			}
			case (sf::Event::KeyReleased):
			{
				keyEvent = KeyUp;
				break;
			}
			default:
			{
				// error
				return;
			}
		}
		if (binding.Controller)
		{
			binding.Controller->ProcessInputAction(binding.Action, keyEvent);
		}
	}
}
