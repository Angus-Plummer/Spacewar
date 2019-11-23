#pragma once
#include <vector>

class World;
class Controller;

class GameMode
{
public:
	GameMode();
	~GameMode();

	void Initialise();

	void Update(const float deltaTime);

	World* GetWorld() const;

	std::vector<Controller*> GetControllers;

protected:
	World* mWorld;
	std::vector<Controller*> mControllers;
};