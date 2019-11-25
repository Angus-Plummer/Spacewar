#include "GameMode.h"
#include "Controller.h"

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

}

void GameMode::Update(const float deltaTime)
{
	for (std::map<int, Controller*>::iterator controllerIter = mControllers.begin(); controllerIter != mControllers.end(); ++controllerIter)
	{

	}
}

Controller* GameMode::GetController(int id) const
{
	Controller* controller = nullptr;
	auto findIter = mControllers.find(id);
	if (findIter != mControllers.end())
	{
		controller = (findIter->second);
	}
	return controller;
}
