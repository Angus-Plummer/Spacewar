#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class WorldObject;
class GameMode;
class InputManager;

class GameInstance
{
public:
	GameInstance();
	~GameInstance();

	void Initialise();
	void Update(const float deltaTime);

	static InputManager* GetInputManager();

	static sf::RenderWindow* GetGameWindow();
	bool mWindowHasFocus;

	bool GetIsRunning() const;
private:
	bool mIsRunning;
	static sf::RenderWindow* kGameWindow;
	static InputManager* kInputManager;
	GameMode* mGameMode;
};