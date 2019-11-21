#include "GameState.h"
#include "Math/Vector2D.h"
#include "World/WorldObject.h"
#include "World/SpaceShip.h"

GameState::GameState()
{
}

GameState::~GameState()
{
	for (int i = 0; i < mGameObjects.size(); i++)
	{
		delete mGameObjects[i];
	}
	mGameObjects.clear();
}

void GameState::Initialise()
{
	SpaceShip* lonelyShip = new SpaceShip();
	lonelyShip->SetVelocity(Vector2D(15.0f, 10.0f));
	mGameObjects.push_back(lonelyShip);
}

void GameState::Update(const float deltaTime)
{
	UpdateGameObjects(deltaTime);
}

void GameState::UpdateGameObjects(const float deltaTime)
{
	for (int i = 0; i < mGameObjects.size(); i++)
	{
		WorldObject* currentObject = mGameObjects[i];
		if (currentObject)
		{
			currentObject->Update(deltaTime);
		}
	}
}

const std::vector<WorldObject*>& GameState::GetGameObjects() const
{
	return mGameObjects;
}
