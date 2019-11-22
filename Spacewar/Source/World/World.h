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

protected:
	std::vector<Attractor*> mAttractors;
	std::vector<SpaceShip*> mShips;
	std::vector<Debris*> mDebris;

	std::vector<WorldObject*> GetAllObjectsInWorld();

	// calls update on the world objects
	void UpdateWorldObjects(const float deltaTime);

	void ApplyPhysics(const float deltaTime);
};