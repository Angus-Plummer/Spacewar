#include "GameMode.h"
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

	// create the controllers
	Controller* playerController = new Controller();
	playerController->Initialise();
	mControllers.push_back(playerController);

	// create the player ship and add to the world
	SpaceShip* playerShip = nullptr;
	for (int i = 0; i < 6; i++)
	{
		playerShip = new SpaceShip();
		playerShip->SetPosition(Vector2D(rand() % 1280, rand() % 720));
		playerShip->SetVelocity(Vector2D(rand() % 150 - 75, rand() % 150 - 75));
		mWorld->AddShip(playerShip);
	}
	
	playerController->SetShip(playerShip);

	// create the star
	Attractor* star1 = new Attractor(2.0f);
	star1->SetPosition(Vector2D(1280.0f / 3.0f, 720.0f / 2.0f));
	star1->SetVelocity(Vector2D(0.0f, -50.0f));
	mWorld->AddAttractor(star1);

	Attractor* star2 = new Attractor(2.0f);
	star2->SetPosition(Vector2D(2.0f * 1280.0f / 3.0f, 720.0f / 2.0f));
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
