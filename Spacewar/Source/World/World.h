#pragma once
#include <vector>

class WorldObject;
class Attractor;
class SpaceShip;
class Debris;

class World
{
public:
	World();
	~World();

	void Update(const float deltaTime);

	void AddAttractor(Attractor* newAttractor);
	void AddShip(SpaceShip* newShip);
	void AddDebris(Debris* newDebris);
	void AddDebris(std::vector<Debris*> newDebris);
	void RemoveWorldObject(WorldObject* worldObject);

protected:
	std::vector<Attractor*> mAttractors;
	std::vector<SpaceShip*> mShips;
	std::vector<Debris*> mDebris;

	void RemoveAttractor(Attractor* attractor);
	void RemoveShip(SpaceShip* ship);
	void RemoveDebris(Debris* debris);

	std::vector<WorldObject*> GetAllObjectsInWorld();

	// calls update on the world objects
	void UpdateWorldObjects(const float deltaTime);
	void ApplyPhysicsInteraction(const float deltaTime);
	void ApplyCollisions();
	void ApplyCollision(WorldObject* object1, WorldObject* object2);
	void ApplyAttractors(std::vector<WorldObject*>& targetObjects);
};