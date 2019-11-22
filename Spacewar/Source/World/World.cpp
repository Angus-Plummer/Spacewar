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
	ApplyPhysicsInteraction(deltaTime);
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
	allObjects.insert(allObjects.end(), mDebris.begin(), mDebris.end());
	allObjects.insert(allObjects.end(), mShips.begin(), mShips.end());
	allObjects.insert(allObjects.end(), mAttractors.begin(), mAttractors.end());

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

void World::ApplyCollisions()
{
	std::vector<WorldObject*> worldObjects = GetAllObjectsInWorld();
	
	// all - attractor collisions
	for (int i = 0; i < worldObjects.size(); i++)
	{
		WorldObject* currentObject = worldObjects[i];
		if (currentObject->GetIsCollisionEnabled())
		{
			for (int j = 0; j < mAttractors.size(); j++)
			{
				Attractor* attractor = mAttractors[j];
				ApplyCollision(currentObject, attractor);
			}
		}
	}

	mDebris.erase(std::remove_if(mDebris.begin(), mDebris.end(), [](Debris* debris) {return (!debris->IsAlive()); }), mDebris.end());

	// ship - ship collisions
	for (int i = 0; i + 1 < mShips.size(); i++)
	{
		SpaceShip* currentShip = mShips[i];
		for (int j = i + 1; j < mShips.size(); j++)
		{
			SpaceShip* otherShip = mShips[j];
			ApplyCollision(currentShip, otherShip);
		}
	}

	// create debris from dead ships and destroy them
	for (int i = 0; i < mShips.size(); i++)
	{
		SpaceShip* ship = mShips[i];
		if (!ship->IsAlive())
		{
			std::vector<Debris*> generatedDebris = ship->GenerateDebris(200);
			AddDebris(generatedDebris);
		}
	}

	// remove dead ships
	mShips.erase(std::remove_if(mShips.begin(), mShips.end(), [](SpaceShip* ship) {return (!ship->IsAlive()); }), mShips.end());

}

void World::ApplyCollision(WorldObject* object1, WorldObject* object2)
{
	if (object1 == object2)
	{
		// ignore self
		return;
	}
	if (object1->GetIsCollisionEnabled() && object2->GetIsCollisionEnabled())
	{
		// collision if separation is less than sum of collision radii
		Vector2D deltaPos = object2->GetPosition() - object1->GetPosition();
		float separation = deltaPos.Magnitude();
		float collisionSeparation = object1->GetCollisionRadius() + object2->GetCollisionRadius();
		if (separation < collisionSeparation)
		{
			// collision
			object1->OnCollision();
			object2->OnCollision();
		}
	}
}

void World::ApplyAttractors(std::vector<WorldObject*>& targetObjects)
{
	// apply attractor force
	for (int i = 0; i < targetObjects.size(); i++)
	{
		WorldObject* targetObject = targetObjects[i];

		// apply the force from each attractor
		for (int j = 0; j < mAttractors.size(); j++)
		{
			Attractor* attractor = mAttractors[j];

			// do not apply attractor force to itself
			if (attractor == targetObject)
			{
				continue;
			}

			attractor->ApplyForce(targetObject);
		}
	}
}

void World::ApplyPhysicsInteraction(const float deltaTime)
{
	ApplyCollisions();
	
	// objects may have been added or removed during collision
	std::vector<WorldObject*> worldObjects = GetAllObjectsInWorld();
	ApplyAttractors(worldObjects);
}