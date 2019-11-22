#include "GameInstance.h"
#include "GameMode.h"
#include "World/World.h"
#include "World/WorldObject.h"

sf::RenderWindow* GameInstance::kGameWindow = nullptr;

GameInstance::GameInstance()
	: mIsRunning(false)
{
}

GameInstance::~GameInstance()
{
	delete kGameWindow;
	delete mGameMode;
}

void GameInstance::Initialise()
{
	mIsRunning = true;

	// Initialise Game Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	kGameWindow = new sf::RenderWindow(sf::VideoMode(1280, 720), "Spacewar!", sf::Style::Default, settings);
	kGameWindow->setFramerateLimit(60);

	// Initialise Game Mode
	mGameMode = new GameMode();
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
	}
	if (mIsRunning)
	{
		kGameWindow->clear();

		mGameMode->Update(deltaTime);

		kGameWindow->display();
	}
}

sf::RenderWindow * GameInstance::GetGameWindow()
{
	return kGameWindow;
}

bool GameInstance::GetIsRunning() const
{
	return mIsRunning;
}
