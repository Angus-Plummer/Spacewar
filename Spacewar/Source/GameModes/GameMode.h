#pragma once
#include <vector>
#include <map>

class Controller;

class GameMode
{
public:
	GameMode();
	~GameMode();

	virtual void Initialise();

	virtual void Update(const float deltaTime) = 0;

	//std::vector<Controller*> GetControllers();

protected:
	int mNumPlayers;
	std::map<int, Controller*> mControllers;
};