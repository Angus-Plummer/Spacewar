#include "BattleMode.h"
#include "../GameInstance.h"
#include "../Math/Vector2D.h"
#include "BattleController.h"
#include "World.h"
#include "WorldObject.h"
#include "SpaceShip.h"
#include "Attractor.h"

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

	// create the controllers
	for (int i = 0; i < mNumPlayers; i++)
	{
		BattleController* playerController = new BattleController(i);
		playerController->Initialise();
		mControllers[i] = playerController;
	}

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

		BattleController* battleController = GetBattleController(i);
		if (battleController)
		{
			battleController->SetShip(spawnedShip);
		}
	}

	// create binary stars
	float separation = 150.0f; // = r1 + r2
	Attractor* star1 = new Attractor(1.0f);
	Attractor* star2 = new Attractor(1.0f);
	star1->SetMass(10000000.0f);
	star2->SetMass(10000000.0f);
	
	//float orbitalRadiusRatio = sqrt((star1->GetAttractionFactor() * star1->GetMass()) / (star2->GetAttractionFactor() * star2->GetMass())); // = r1/r2
	float orbitalRadiusRatio = (star1->GetAttractionFactor() * star1->GetMass()) / (star2->GetAttractionFactor() * star2->GetMass()); // = r1/r2

	float r1 = separation / (1.0f + orbitalRadiusRatio);
	float r2 = separation - r1;
	star1->SetPosition(Vector2D(-r1 , 0.0f));
	star2->SetPosition(Vector2D(r2, 0.0f));

	float v1 = sqrt(star2->GetAttractionFactor() * star2->GetMass() * r1) / separation;
	float v2 = r2 / r1 * v1;

	star1->SetVelocity(Vector2D(0.0f, v1));
	star2->SetVelocity(Vector2D(0.0f, -v2));

	mWorld->AddAttractor(star1);
	mWorld->AddAttractor(star2);
}

void BattleMode::Update(const float deltaTime)
{
	mWorld->Update(deltaTime);
}

World* BattleMode::GetWorld() const
{
	return mWorld;

}

BattleController * BattleMode::GetBattleController(int id) const
{
	Controller* controller = GetController(id);
	BattleController* battleController = dynamic_cast<BattleController*>(controller);
	return battleController;
}
