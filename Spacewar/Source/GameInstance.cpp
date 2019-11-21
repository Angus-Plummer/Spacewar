#include "GameInstance.h"
#include "World/WorldObject.h"
#include "GameState.h"

GameInstance::GameInstance()
	: mIsRunning(false)
	, mGameWindow(nullptr)
{
}

GameInstance::~GameInstance()
{
	delete mGameWindow;
	delete mGameState;
}

void GameInstance::Initialise()
{
	mIsRunning = true;

	// Initialise Game Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	mGameWindow = new sf::RenderWindow(sf::VideoMode(1280, 720), "Spacewar!", sf::Style::Default, settings);
	mGameWindow->setFramerateLimit(60);

	// Initialise Game State
	mGameState = new GameState();
	mGameState->Initialise();
}

void GameInstance::Update(const float deltaTime)
{
	sf::Event event;
	while (mGameWindow->pollEvent(event))
	{
		// poll for window closed event
		if (event.type == sf::Event::Closed)
		{
			mGameWindow->close();
			mIsRunning = false;
		}
	}
	if (mIsRunning)
	{
		mGameWindow->clear();

		mGameState->Update(deltaTime);
		DrawGameObjects(); // TODO: move this to separate gamestate observer class

		mGameWindow->display();
	}
}

void GameInstance::DrawGameObjects()
{
	const std::vector<WorldObject*>& gameObjects = mGameState->GetGameObjects();
	for (int i = 0; i < gameObjects.size(); i++)
	{
		const WorldObject* currentGameObject = gameObjects[i];
		const sf::Shape* objectShape = currentGameObject->GetShape();
		if (objectShape)
		{
			mGameWindow->draw(*objectShape);
		}
	}
}

bool GameInstance::GetIsRunning() const
{
	return mIsRunning;
}
