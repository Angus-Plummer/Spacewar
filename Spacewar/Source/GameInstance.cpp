#include "GameInstance.h"
#include "Battle/BattleMode.h"
#include <SFML/Window.hpp>
#include "Input/InputManager.h"

sf::RenderWindow* GameInstance::kGameWindow = nullptr;
InputManager* GameInstance::kInputManager = nullptr;

GameInstance::GameInstance()
	: mIsRunning(false)
	, mWindowHasFocus(true)
{
}

GameInstance::~GameInstance()
{
	delete kGameWindow;
	kGameWindow = nullptr;

	delete kInputManager;
	kInputManager = nullptr;

	delete mGameMode;
}

void GameInstance::Initialise()
{
	mIsRunning = true;

	// Initialise Game Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	kGameWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Spacewar!", sf::Style::Default, settings);
	kGameWindow->setVerticalSyncEnabled(true);

	// Initialise Input Manager
	kInputManager = new InputManager();

	// Initialise Game Mode
	mGameMode = new BattleMode(2);
	mGameMode->Initialise();
}

void GameInstance::Update(const float deltaTime)
{
	sf::Event event;
	while (kGameWindow->pollEvent(event))
	{
		// poll for window closed event
		if (event.type == sf::Event::Closed)
		{
			kGameWindow->close();
			mIsRunning = false;
		}
		else if (event.type == sf::Event::LostFocus)
		{
			mWindowHasFocus = false;
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			mWindowHasFocus = true;
		}
		else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			kInputManager->ProcessInput(event.key.code, event.type);
		}
	}

	if (mIsRunning && mWindowHasFocus)
	{
		kGameWindow->clear();

		mGameMode->Update(deltaTime);

		kGameWindow->display();
	}
}

InputManager* GameInstance::GetInputManager()
{
	return kInputManager;
}

sf::RenderWindow* GameInstance::GetGameWindow()
{
	return kGameWindow;
}

bool GameInstance::GetIsRunning() const
{
	return mIsRunning;
}
