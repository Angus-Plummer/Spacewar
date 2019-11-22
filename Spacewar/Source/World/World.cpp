#include "World.h"
#include "WorldObject.h"
#include "Attractor.h"
#include "SpaceShip.h"
#include <algorithm>

World::World()
{
}

World::~World()
{
	for (int i = 0; i < mAttractors.size(); i++)
	{
		delete mAttractors[i];
	}
	mAttractors.clear();

	for (int i = 0; i < mShips.size(); i++)
	{
		delete mShips[i];
	}
	mShips.clear();
}

void World::Update(const float deltaTime)
{
	ApplyPhysics(deltaTime);
	UpdateWorldObjects(deltaTime);
}

void World::AddAttractor(Attractor * newAttractor)
{
	mAttractors.push_back(newAttractor);
}

void World::AddShip(SpaceShip * newShip)
{
	mShips.push_back(newShip);
}

/*
void World::DestroyObject(WorldObject * objectToDestroy)
{
	// TODO: optimise this
	std::vector<WorldObject*>::iterator item = std::find(mWorldObjects.begin(), mWorldObjects.end(), objectToDestroy);
	if (item != mWorldObjects.end())
	{
		delete *item;
		mWorldObjects.erase(item);
	}
}*/

void World::UpdateWorldObjects(const float deltaTime)
{
	for (int i = 0; i < mAttractors.size(); i++)
	{
		Attractor* attractor = mAttractors[i];
		if (attractor)
		{
			attractor->Update(deltaTime);
		}
	}
	for (int i = 0; i < mShips.size(); i++)
	{
		SpaceShip* ship = mShips[i];
		if (ship)
		{
			ship->Update(deltaTime);
		}
	}
}

void World::ApplyPhysics(const float deltaTime)
{
	// for each ship, apply the force from each attractor
	for (int i = 0; i < mShips.size(); i++)
	{
		SpaceShip*& ship = mShips[i];
		for (int j = 0; j < mAttractors.size(); j++)
		{
			Attractor* attractor = mAttractors[j];

			// if ship is within the death distance of the attractor then destroy it
			Vector2D deltaPos = ship->GetPosition() - attractor->GetPosition();
			float separation = deltaPos.Magnitude();
			if (separation < attractor->GetDeathDistance())
			{
				ship->Kill();
				break;
			}

			attractor->ApplyForce(ship);
		}
	}
	// remove dead ships
	mShips.erase(std::remove_if(mShips.begin(), mShips.end(), [](SpaceShip* ship) {return (!ship->IsAlive()); }), mShips.end());
}

std::vector<const WorldObject*> World::GetWorldObjects() const
{
	//  TODO: this is inefficient. Find better way of doing this
	std::vector<const WorldObject*> allWorldObjects;
	for (int i = 0; i < mAttractors.size(); i++)
	{
		allWorldObjects.push_back(mAttractors[i]);
	}
	for (int i = 0; i < mShips.size(); i++)
	{
		allWorldObjects.push_back(mShips[i]);
	}
	return allWorldObjects;
}
