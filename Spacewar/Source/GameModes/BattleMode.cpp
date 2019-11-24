#include "BattleMode.h"
#include "../GameInstance.h"
#include "../Math/Vector2D.h"
#include "../Controller.h"
#include "../World/World.h"
#include "../World/WorldObject.h"
#include "../World/SpaceShip.h"
#include "../World/Attractor.h"

BattleMode::BattleMode(int numPlayers)
	: GameMode()
	, mWorld(nullptr)
{
	mNumPlayers = numPlayers;
}

BattleMode::~BattleMode()
{
	delete mWorld;
}

void BattleMode::Initialise()
{
	GameMode::Initialise();

	// create the game world
	mWorld = new World();
	sf::RenderWindow* gameWindow = GameInstance::GetGameWindow();
	Vector2D windowSize((float)(gameWindow->getSize().x), (float)(gameWindow->getSize().y));
	mWorld->SetOrigin(windowSize / 2.0f);
	mWorld->SetBounds(mWorld->ScreenToWorldPos(windowSize * 0.1f), mWorld->ScreenToWorldPos(windowSize * (0.9f)));
	mWorld->Initialise();

	// spawn the ships
	int numShips = mNumPlayers + 4;
	for (int i = 0; i < numShips; i++)
	{
		SpaceShip* spawnedShip = new SpaceShip();
		Vector2D spawnPos = mWorld->GetLowerBound();
		spawnPos += Vector2D((float)(rand() % 600) - 300.0f, (float)(rand() % 600) - 300.0f);
		spawnedShip->SetPosition(spawnPos);
		spawnedShip->SetVelocity(Vector2D((float)(rand() % 100 - 50.0f), (float)(rand() % 100 - 50.0f)));
		mWorld->AddShip(spawnedShip);

		if (mControllers.count(i) == 1)
		{
			mControllers[i]->SetShip(spawnedShip);
		}
	}

	// create the stars
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

void BattleMode::Update(const float deltaTime)
{
	mWorld->Update(deltaTime);

	for (std::map<int, Controller*>::iterator controllerIter = mControllers.begin(); controllerIter != mControllers.end(); ++controllerIter)
	{

	}
}

World* BattleMode::GetWorld() const
{
	return mWorld;

}
