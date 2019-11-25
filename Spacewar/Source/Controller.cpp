#include "Controller.h"
#include "GameInstance.h"
#include "Input/InputManager.h"

Controller::Controller(int id) 
	: mId(id)
{
}

void Controller::Initialise()
{
	SetupInput();
}

void Controller::RegisterInputBinding(InputAction action, sf::Keyboard::Key key)
{
	InputManager* inputManager = GameInstance::GetInputManager();
	inputManager->AddBinding(this, key, action);
}

void Controller::SetupInput()
{
}