#include "GameMode.h"
#include "../Controller.h"

GameMode::GameMode() : mNumPlayers(1)
{
}

GameMode::~GameMode()
{
	// destroy the controllers
	for (std::map<int, Controller*>::iterator it; it != mControllers.end(); ++it)
	{
		delete it->second;
	}
	mControllers.clear();
}

void GameMode::Initialise()
{
	// create the controllers
	for (int i = 0; i < mNumPlayers; i++)
	{
		Controller* playerController = new Controller(i);
		playerController->Initialise();
		mControllers[i] = playerController;
	}
}
