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
	, mState(BattleState::Initialising)
	, mStateTimer(0.0f)
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

	SetupWorld();

	mState = BattleState::ReadyCheck;
	mStateTimer = 1.0f;
}

void BattleMode::Update(const float deltaTime)
{
	mStateTimer = std::max(0.0f, mStateTimer - deltaTime);
	switch (mState)
	{
		case(BattleState::ReadyCheck):
		{
			if (mStateTimer <= 0.0f)
			{
				mState = BattleState::Playing;
			}
			break;
		}
		case(BattleState::Playing):
		{
			mWorld->Update(deltaTime);
			bool isRoundOver = IsRoundOver();
			if (isRoundOver)
			{
				mState = BattleState::RoundOver;
				mStateTimer = 2.0f;
			}
			break;
		}
		case (BattleState::RoundOver):
		{
			mWorld->Update(deltaTime);
			if (mStateTimer <= 0.0f)
			{
				delete mWorld;
				SetupWorld();
				mStateTimer = 1.0f;
				mState = BattleState::ReadyCheck;
			}
			break;
		}
	}
	if (mWorld)
	{
		sf::RenderWindow* gameWindow = GameInstance::GetGameWindow();
		mWorld->Draw(gameWindow);
	}
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

bool BattleMode::IsRoundOver() const
{
	int numPlayersAlive = 0;
	for (int i = 0; i < mNumPlayers; i++)
	{
		BattleController* player = GetBattleController(i);
		if (player)
		{
			SpaceShip* playerShip = player->GetShip();
			if (playerShip && playerShip->IsAlive())
			{
				numPlayersAlive++;
			}
		}
	}
	return numPlayersAlive <= 1;
}

void BattleMode::SetupWorld()
{
	// create the game world
	mWorld = new World();
	sf::RenderWindow* gameWindow = GameInstance::GetGameWindow();
	Vector2D windowSize((float)(gameWindow->getSize().x), (float)(gameWindow->getSize().y));
	mWorld->SetOrigin(windowSize / 2.0f);
	mWorld->SetBounds(mWorld->ScreenToWorldPos(windowSize * 0.1f), mWorld->ScreenToWorldPos(windowSize * (0.9f)));
	mWorld->Initialise();

	// spawn the ships
	int numShips = mNumPlayers;// +4;
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
	float separation = 100.0f + rand() % 300;
	float star1Strength = 0.5f + 4.5f * (rand() % 100 / 100.0f);
	float star2Strength = 0.5f + 4.5f * (rand() % 100 / 100.0f);
	Attractor* star1 = new Attractor(star1Strength);
	Attractor* star2 = new Attractor(star2Strength);

	//float orbitalRadiusRatio = sqrt((star1->GetAttractionFactor() * star1->GetMass()) / (star2->GetAttractionFactor() * star2->GetMass())); // = r1/r2
	float orbitalRadiusRatio = (star1->GetAttractionFactor() * star1->GetMass()) / (star2->GetAttractionFactor() * star2->GetMass()); // = r1/r2

	float r1 = separation / (1.0f + orbitalRadiusRatio);
	float r2 = separation - r1;
	star1->SetPosition(Vector2D(-r1, 0.0f));
	star2->SetPosition(Vector2D(r2, 0.0f));

	float v1 = sqrt(star2->GetAttractionFactor() * star2->GetMass() * r1) / separation;
	float v2 = r2 / r1 * v1;

	star1->SetVelocity(Vector2D(0.0f, v1));
	star2->SetVelocity(Vector2D(0.0f, -v2));

	mWorld->AddAttractor(star1);
	mWorld->AddAttractor(star2);
}
