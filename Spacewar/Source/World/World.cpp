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
	newAttractor->SetWorld(this);
}

void World::RemoveAttractor(Attractor * attractor)
{
	std::vector<Attractor*>::iterator attractorIt = std::remove(mAttractors.begin(), mAttractors.end(), attractor);
	mAttractors.erase(attractorIt, mAttractors.end());
	delete attractor;
}

void World::AddShip(SpaceShip * newShip)
{
	mShips.push_back(newShip);
	newShip->SetWorld(this);
}

void World::RemoveShip(SpaceShip * ship)
{
	std::vector<SpaceShip*>::iterator shipIt = std::remove(mShips.begin(), mShips.end(), ship);
	mShips.erase(shipIt, mShips.end());
	delete ship;
}

void World::AddDebris(Debris * newDebris)
{
	mDebris.push_back(newDebris);
	newDebris->SetWorld(this);
}

void World::AddDebris(std::vector<Debris*> newDebris)
{
	for (int i = 0; i < newDebris.size(); i++)
	{
		newDebris[i]->SetWorld(this);
	}
	mDebris.insert(mDebris.end(), newDebris.begin(), newDebris.end());
}

void World::RemoveWorldObject(WorldObject * worldObject)
{
	// TODO : find cleaner nice OOP way to do this
	Debris* debris = dynamic_cast<Debris*>(worldObject);
	if (debris)
	{
		RemoveDebris(debris);
	}
	else
	{
		SpaceShip* ship = dynamic_cast<SpaceShip*>(worldObject);
		if (ship)
		{
			RemoveShip(ship);
		}
		else
		{
			Attractor* attractor = dynamic_cast<Attractor*>(worldObject);
			if (attractor)
			{
				RemoveAttractor(attractor);
			}
		}
	}
}

void World::RemoveDebris(Debris * debris)
{
	std::vector<Debris*>::iterator debrisIt = std::remove(mDebris.begin(), mDebris.end(), debris);
	mDebris.erase(debrisIt, mDebris.end());
	delete debris;
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
		if (!worldObject->IsAlive())
		{
			RemoveWorldObject(worldObject);
		}
		else
		{
			worldObject->Update(deltaTime);
		}
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