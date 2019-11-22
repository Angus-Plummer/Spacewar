#include "World.h"
#include "WorldObject.h"
#include "Attractor.h"
#include "SpaceShip.h"
#include "Debris.h"
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

	for (int i = 0; i < mDebris.size(); i++)
	{
		delete mDebris[i];
	}
	mDebris.clear();
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

void World::AddDebris(Debris * newDebris)
{
	mDebris.push_back(newDebris);
}

void World::AddDebris(std::vector<Debris*> newDebris)
{
	mDebris.insert(mDebris.end(), newDebris.begin(), newDebris.end());
}

std::vector<WorldObject*> World::GetAllObjectsInWorld()
{
	std::vector<WorldObject*> allObjects;
	allObjects.insert(allObjects.end(), mAttractors.begin(), mAttractors.end());
	allObjects.insert(allObjects.end(), mShips.begin(), mShips.end());
	allObjects.insert(allObjects.end(), mDebris.begin(), mDebris.end());

	return allObjects;
}

void World::UpdateWorldObjects(const float deltaTime)
{
	std::vector<WorldObject*> worldObjects = GetAllObjectsInWorld();
	for (int i = 0; i < worldObjects.size(); i++)
	{
		WorldObject* worldObject = worldObjects[i];
		worldObject->Update(deltaTime);
	}
}

void World::ApplyPhysics(const float deltaTime)
{
	// for each worldObject, apply the force from each attractor
	std::vector<WorldObject*> worldObjects = GetAllObjectsInWorld();
	for (int i = 0; i < worldObjects.size(); i++)
	{
		WorldObject*& worldObject = worldObjects[i];

		for (int j = 0; j < mAttractors.size(); j++)
		{
			Attractor* attractor = mAttractors[j];

			// do not apply attractor force to itself
			if (attractor == worldObject)
			{
				continue;
			}

			// if ship is within the death distance of the attractor then destroy it
			Vector2D deltaPos = worldObject->GetPosition() - attractor->GetPosition();
			float separation = deltaPos.Magnitude();
			
			if (separation < attractor->GetDeathDistance())
			{
				SpaceShip* ship = dynamic_cast<SpaceShip*>(worldObject);
				if (ship)
				{
					std::vector<Debris*> generatedDebris = ship->GenerateDebris(50);
					// add debris to current pass of world objects so they will be affected by the attractors upon creation
					worldObjects.insert(worldObjects.end(), generatedDebris.begin(), generatedDebris.end());
					// add debris to world
					AddDebris(generatedDebris);
					ship->Kill();
				}
				break;
			}
			
			attractor->ApplyForce(worldObject);
		}
	}

	// remove dead ships
	mShips.erase(std::remove_if(mShips.begin(), mShips.end(), [](SpaceShip* ship) {return (!ship->IsAlive()); }), mShips.end());
}