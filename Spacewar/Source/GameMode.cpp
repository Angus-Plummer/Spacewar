#include "GameMode.h"
#include "GameInstance.h"
#include "Math/Vector2D.h"
#include "Controller.h"
#include "World/World.h"
#include "World/WorldObject.h"
#include "World/SpaceShip.h"
#include "World/Attractor.h"

GameMode::GameMode()
{
}

GameMode::~GameMode()
{
	delete mWorld;

	// destroy the controllers
	for (int i = 0; i < mControllers.size(); i++)
	{
		delete mControllers[i];
	}
	mControllers.clear();
}

void GameMode::Initialise()
{
	// create the game world
	mWorld = new World();
	sf::RenderWindow* gameWindow = GameInstance::GetGameWindow();
	Vector2D windowSize((float)(gameWindow->getSize().x), (float)(gameWindow->getSize().y));
	mWorld->SetOrigin(windowSize / 2.0f);
	mWorld->SetBounds(mWorld->ScreenToWorldPos(windowSize * 0.1f), mWorld->ScreenToWorldPos(windowSize * (0.9f)));

	// create the controllers
	Controller* playerController = new Controller();
	playerController->Initialise();
	mControllers.push_back(playerController);

	// create the player ship and add to the world
	SpaceShip* playerShip = nullptr;
	for (int i = 0; i < 6; i++)
	{
		playerShip = new SpaceShip();
		Vector2D spawnPos = mWorld->GetLowerBound();
		spawnPos += Vector2D((float)(rand() % 600) - 300.0f, (float)(rand() % 600) - 300.0f);
		playerShip->SetPosition(spawnPos);
		playerShip->SetVelocity(Vector2D((float)(rand() % 100 - 50.0f), (float)(rand() % 100 - 50.0f)));
		mWorld->AddShip(playerShip);
	}
	
	playerController->SetShip(playerShip);

	// create the star
	Attractor* star1 = new Attractor(2.0f);
	//star1->SetPosition(Vector2D(0.0f, 0.0f));
	star1->SetPosition(Vector2D(-200.0f, 0.0f));
	star1->SetVelocity(Vector2D(0.0f, -50.0f));
	mWorld->AddAttractor(star1);

	Attractor* star2 = new Attractor(2.0f);
	star2->SetPosition(Vector2D(200.0f, 0.0f));
	star2->SetVelocity(Vector2D(0.0f, 50.0f));
	mWorld->AddAttractor(star2);
}

void GameMode::Update(const float deltaTime)
{
	mWorld->Update(deltaTime);
}

World* GameMode::GetWorld() const
{
	return mWorld;
}
