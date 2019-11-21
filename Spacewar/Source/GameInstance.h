#pragma once
#include <SFML/Graphics.hpp>

class WorldObject;
class GameMode;

class GameInstance
{
public:
	GameInstance();
	~GameInstance();
	void Initialise();
	void Update(const float deltaTime);

	void DrawGameObjects();

	bool GetIsRunning() const;
private:
	bool mIsRunning;
	sf::RenderWindow* mGameWindow;
	GameMode* mGameState;
};