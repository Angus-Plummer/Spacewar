#pragma once
#include <vector>
#include "../Math/Vector2D.h"
#include "../Drawable.h"

class WorldObject;
class Attractor;
class SpaceShip;
class Bullet;
class Debris;

struct BackgroundStarLayer
{
	// TODO: replace array of stars with a transparent texture of stars
	std::vector<sf::CircleShape> Stars;
	Vector2D Velocity;
};


class World : public Drawable
{
public:
	World();
	~World();

	void Initialise();
	void Update(const float deltaTime);

	Vector2D GetLowerBound() const;
	Vector2D GetUpperBound() const;
	void SetBounds(std::pair<Vector2D, Vector2D> bounds);
	void SetBounds(Vector2D lowerBound, Vector2D upperBound);

	Vector2D GetOrigin() const;
	void SetOrigin(Vector2D origin);

	Vector2D WorldToScreenPos(Vector2D worldPosition);
	Vector2D ScreenToWorldPos(Vector2D screenPosition);

	Vector2D WrapAround(Vector2D position);
	bool IsWithinBounds(Vector2D position);

	void AddAttractor(Attractor* newAttractor);
	void AddShip(SpaceShip* newShip);
	void AddBullet(Bullet* newBullet);
	void AddDebris(Debris* newDebris);
	void AddDebris(std::vector<Debris*> newDebris);
	void RemoveWorldObject(WorldObject* worldObject);

protected:
	std::pair<Vector2D, Vector2D> mBounds;
	Vector2D mOrigin;

	std::vector<Attractor*> mAttractors;
	std::vector<SpaceShip*> mShips;
	std::vector<Bullet*> mBullets;
	std::vector<Debris*> mDebris;

	void RemoveAttractor(Attractor* attractor);
	void RemoveShip(SpaceShip* ship);
	void RemoveBullet(Bullet* bullet);
	void RemoveDebris(Debris* debris);

	std::vector<WorldObject*> GetAllObjectsInWorld();

	// calls update on the world objects
	void UpdateWorldObjects(const float deltaTime);
	void ApplyPhysicsInteraction(const float deltaTime);
	void ApplyCollisions();
	void ApplyCollision(WorldObject* object1, WorldObject* object2);
	void ApplyAttractors(std::vector<WorldObject*>& targetObjects);

	// Drawable Implementation.
protected:
	virtual void Draw(sf::RenderWindow* drawWindow) override;
	sf::RectangleShape mBoxBounds;

	void InitialiseBackground();
	std::vector<BackgroundStarLayer> mBackgroundStars;
};