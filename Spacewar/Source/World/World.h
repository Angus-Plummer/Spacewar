#pragma once
#include <vector>

class WorldObject;
class Attractor;
class SpaceShip;

class World
{
public:
	World();
	~World();

	void Update(const float deltaTime);

	void AddAttractor(Attractor* newAttractor);
	void AddShip(SpaceShip* newShip);

	void DestroyObject(WorldObject* objectToDestroy);

	std::vector<const WorldObject*> GetWorldObjects() const; // for observers

protected:
	std::vector<Attractor*> mAttractors;
	std::vector<SpaceShip*> mShips;

	// calls update on the world objects
	void UpdateWorldObjects(const float deltaTime);

	void ApplyPhysics(const float deltaTime);
};