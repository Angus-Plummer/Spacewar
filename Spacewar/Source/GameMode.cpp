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
	mControllers.push_back(playerController);

	// create the player ship and add to the world
	for (int i = 0; i < 20; i++)
	{
		SpaceShip* playerShip = new SpaceShip();
		playerShip->SetPosition(Vector2D(rand() % 1280, rand() % 720));
		playerShip->SetVelocity(Vector2D(rand() % 150 - 75, rand() % 150 - 75));
		mWorld->AddShip(playerShip);
	}
	
	//playerController->SetShip(playerShip);

	// create the star
	Attractor* star = new Attractor(1.0f, 15.0f);
	star->SetPosition(Vector2D(1280.0f / 2.0f, 720.0f / 2.0f));
	mWorld->AddAttractor(star);
}

void GameMode::Update(const float deltaTime)
{
	mWorld->Update(deltaTime);
}

World* GameMode::GetWorld() const
{
	return mWorld;
}
