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
	static sf::RenderWindow* GetGameWindow();

	bool GetIsRunning() const;
private:
	bool mIsRunning;
	static sf::RenderWindow* kGameWindow;
	GameMode* mGameMode;
};