#pragma once
#include <map>

class Controller;

class GameMode
{
public:
	GameMode();
	~GameMode();

	virtual void Initialise();

	virtual void Update(const float deltaTime) = 0;

	Controller* GetController(int id) const;

protected:
	int mNumPlayers;
	std::map<int, Controller*> mControllers;
};