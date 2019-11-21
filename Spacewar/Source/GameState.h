#pragma once
#include <vector>

class WorldObject;

class GameState
{
public:
	GameState();
	~GameState();

	void Initialise();

	void Update(const float deltaTime);

	// calls update on the game objects
	void UpdateGameObjects(const float deltaTime);
	const std::vector<WorldObject*>& GetGameObjects() const; // for observers

private:
	std::vector<WorldObject*> mGameObjects;
};