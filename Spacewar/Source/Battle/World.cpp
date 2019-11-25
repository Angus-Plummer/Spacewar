#include "World.h"
#include "../GameInstance.h"
#include "WorldObject.h"
#include "Attractor.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include "Debris.h"
#include <algorithm>

World::World()
	: mOrigin(0.0f, 0.0f)
	, mBounds(Vector2D(0.0f, 0.0f), Vector2D(1280.0f, 720.0f))
{
}

World::~World()
{
	std::vector<WorldObject*> worldObjects = GetAllObjectsInWorld();
	for (int i = 0; i < worldObjects.size(); i++)
	{
		delete worldObjects[i];
	}
	mAttractors.clear();
	mShips.clear();
	mDebris.clear();
	mBullets.clear();
}

void World::Initialise()
{
	// initialise bound box
	mBoxBounds.setSize(sf::Vector2f(mBounds.second.X - mBounds.first.X, mBounds.second.Y - mBounds.first.Y));
	Vector2D lowerScreenBound = WorldToScreenPos(mBounds.first);
	mBoxBounds.setPosition(lowerScreenBound.X, lowerScreenBound.Y);
	mBoxBounds.setFillColor(sf::Color::Transparent);

	InitialiseBackground();
}

void World::Update(const float deltaTime)
{
	ApplyPhysicsInteraction(deltaTime);
	UpdateWorldObjects(deltaTime);

	// update background stars
	for (int i = 0; i < mBackgroundStars.size(); i++)
	{
		BackgroundStarLayer& starLayer = mBackgroundStars[i];
		for (int j = 0; j < starLayer.Stars.size(); j++)
		{
			sf::CircleShape& star = starLayer.Stars[j];
			Vector2D starPos(star.getPosition().x, star.getPosition().y);
			starPos += starLayer.Velocity * deltaTime;
			Vector2D worldPos = ScreenToWorldPos(starPos);
			if (!IsWithinBounds(worldPos))
			{
				worldPos = WrapAround(worldPos);
				starPos = WorldToScreenPos(worldPos);
			}
			star.setPosition(sf::Vector2f(starPos.X, starPos.Y));
		}
	}

	sf::RenderWindow* gameWindow = GameInstance::GetGameWindow();
	Draw(gameWindow);
}

Vector2D World::GetLowerBound() const
{
	return mBounds.first;
}

Vector2D World::GetUpperBound() const
{
	return mBounds.second;
}

void World::SetBounds(std::pair<Vector2D, Vector2D> bounds)
{
	mBounds = bounds;
	mBoxBounds.setSize(sf::Vector2f(mBounds.second.X - mBounds.first.X, mBounds.second.Y - mBounds.first.Y));
	Vector2D lowerScreenBound = WorldToScreenPos(mBounds.first);
	mBoxBounds.setPosition(lowerScreenBound.X, lowerScreenBound.Y);
}

void World::SetBounds(Vector2D lowerBound, Vector2D upperBound)
{
	SetBounds(std::pair<Vector2D, Vector2D>(lowerBound, upperBound));
}

Vector2D World::GetOrigin() const
{
	return mOrigin;
}

void World::SetOrigin(Vector2D origin)
{
	mOrigin = origin;
}

Vector2D World::WorldToScreenPos(Vector2D worldPosition)
{
	float scale = 1.0f;
	Vector2D screenPos = (worldPosition / scale) + mOrigin;
	return screenPos;
}

Vector2D World::ScreenToWorldPos(Vector2D screenPosition)
{
	float scale = 1.0f;
	Vector2D worldPos = (screenPosition - mOrigin) * scale;
	return worldPos;
}

void World::AddAttractor(Attractor* newAttractor)
{
	mAttractors.push_back(newAttractor);
	newAttractor->SetWorld(this);
}

void World::RemoveAttractor(Attractor* attractor)
{
	std::vector<Attractor*>::iterator attractorIt = std::remove(mAttractors.begin(), mAttractors.end(), attractor);
	mAttractors.erase(attractorIt, mAttractors.end());
	delete attractor;
}

void World::AddShip(SpaceShip* newShip)
{
	mShips.push_back(newShip);
	newShip->SetWorld(this);
}

void World::AddBullet(Bullet* newBullet)
{
	mBullets.push_back(newBullet);
	newBullet->SetWorld(this);
}

void World::RemoveShip(SpaceShip* ship)
{
	std::vector<SpaceShip*>::iterator shipIt = std::remove(mShips.begin(), mShips.end(), ship);
	mShips.erase(shipIt, mShips.end());
	delete ship;
}

void World::RemoveBullet(Bullet * bullet)
{
	std::vector<Bullet*>::iterator bulletIt = std::remove(mBullets.begin(), mBullets.end(), bullet);
	mBullets.erase(bulletIt, mBullets.end());
	delete bullet;
}

void World::AddDebris(Debris* newDebris)
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
		Bullet* bullet = dynamic_cast<Bullet*>(worldObject);
		if (bullet)
		{
			RemoveBullet(bullet);
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
}

void World::RemoveDebris(Debris * debris)
{
	std::vector<Debris*>::iterator debrisIt = std::remove(mDebris.begin(), mDebris.end(), debris);
	mDebris.erase(debrisIt, mDebris.end());
	delete debris;
}

std::vector<WorldObject*> World::GetAllObjectsInWorld()
{
	// order here determines draw order and order of physics calculations etc
	std::vector<WorldObject*> allObjects;
	allObjects.insert(allObjects.end(), mDebris.begin(), mDebris.end());
	allObjects.insert(allObjects.end(), mBullets.begin(), mBullets.end());
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
		if (worldObject->IsPendingDestroy())
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

	// bullet + ship - ship collisions
	for (int i = 0; i < mShips.size(); i++)
	{
		SpaceShip* currentShip = mShips[i];
		for (int j = i + 1; j < mShips.size(); j++)
		{
			SpaceShip* otherShip = mShips[j];
			ApplyCollision(currentShip, otherShip);
		}

		for (int j = 0; j < mBullets.size(); j++)
		{
			Bullet* bullet = mBullets[j];
			ApplyCollision(currentShip, bullet);
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
			object1->OnCollision(object2);
			object2->OnCollision(object1);
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

void World::Draw(sf::RenderWindow* drawWindow)
{
	// draw background
	for (int i = 0; i < mBackgroundStars.size(); i++)
	{
		BackgroundStarLayer starLayer = mBackgroundStars[i];
		for (int j = 0; j < starLayer.Stars.size(); j++)
		{
			drawWindow->draw(starLayer.Stars[j]);
		}
	}

	// draw all objects in the world
	std::vector<WorldObject*> worldObjects = GetAllObjectsInWorld();
	for (int i = 0; i < worldObjects.size(); i++)
	{
		WorldObject* worldObject = worldObjects[i];
		if (worldObject->IsDrawingEnabled())
		{
			worldObject->Draw(drawWindow);
		}
	}

	// draw the world bounds

	// draw thick outline box to cover up any world objects clipping over the edge of the world bounds
	mBoxBounds.setOutlineColor(sf::Color::Black);
	mBoxBounds.setOutlineThickness(500.0f);
	drawWindow->draw(mBoxBounds);

	// draw thin outline to show world edge
	mBoxBounds.setOutlineColor(sf::Color::White);
	mBoxBounds.setOutlineThickness(2.0f);
	drawWindow->draw(mBoxBounds);
}

void World::InitialiseBackground()
{
	Vector2D lowerScreenBound = WorldToScreenPos(mBounds.first);
	Vector2D upperScreenBound = WorldToScreenPos(mBounds.second);

	Vector2D primaryMovementDirection(-100.0f + rand() % 200, -100.0f + rand() % 200);
	primaryMovementDirection.Normalise();
	float maxSpeed = 15.0f;
	float angleSpread = 45.0f;
	for (int i = 0; i < 20; i++)
	{
		BackgroundStarLayer newStarLayer;
		float angleDeviation = -(angleSpread / 2.0f) + angleSpread * (rand() % 1000 / 1000.0f);
		float speed = maxSpeed * (rand() % 10000 / 10000.0f);
		newStarLayer.Velocity = primaryMovementDirection.Rotated(angleDeviation) * speed;
		for (int j = 0; j < 30; j++)
		{
			float xPos = lowerScreenBound.X + rand() % (int)(upperScreenBound.X - lowerScreenBound.X);
			float yPos = lowerScreenBound.Y + rand() % (int)(upperScreenBound.Y - lowerScreenBound.Y);
			float radius = 1.0f * (rand() % 100) / 100.0f;
			sf::CircleShape newStar(radius, 5);
			newStar.setOrigin(radius, radius);
			newStar.setPosition(sf::Vector2f(xPos, yPos));
			newStar.setFillColor(sf::Color::White);
			newStarLayer.Stars.push_back(newStar);
		}
		mBackgroundStars.push_back(newStarLayer);
	}
}

Vector2D World::WrapAround(Vector2D position)
{
	Vector2D newPos(position);
	// toroidal wrap around

	Vector2D lowerBound = mBounds.first;
	Vector2D upperBound = mBounds.second;
	// avoid div by zero error
	if (upperBound.X != lowerBound.X && upperBound.Y != lowerBound.Y)
	{
		auto ArithmeticModulus = [](float val, float range) {return val - range * floor(val / range); };

		float xmod = ArithmeticModulus(position.X - lowerBound.X, upperBound.X - lowerBound.X);
		float ymod = ArithmeticModulus(position.Y - lowerBound.Y, upperBound.Y - lowerBound.Y);
		newPos.X = lowerBound.X + xmod;
		newPos.Y = lowerBound.Y + ymod;
	}
	return newPos;
}

bool World::IsWithinBounds(Vector2D position)
{
	return !(position.X < mBounds.first.X || position.X > mBounds.second.X
		|| position.Y < mBounds.first.Y || position.Y > mBounds.second.Y);
}

void World::ApplyPhysicsInteraction(const float deltaTime)
{
	ApplyCollisions();
	
	// objects may have been added or removed during collision
	std::vector<WorldObject*> worldObjects = GetAllObjectsInWorld();
	ApplyAttractors(worldObjects);
}