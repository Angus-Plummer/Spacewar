#include "SpaceShip.h"
#include "../GameInstance.h"
#include "Debris.h"
#include "Bullet.h"
#include "World.h"

SpaceShip::SpaceShip()
	: WorldObject()
	, mAmmo(0)
	, mHealth(0.0f)
	, mShipWidth(20.f)
	, mShipLength(30.0f)
{
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	mCollisionRadius = mShipWidth / 2.0f;
	SetupVisual();
}

void SpaceShip::Update(const float deltaTime)
{
	WorldObject::Update(deltaTime);
}

void SpaceShip::FireBullet()
{
	Bullet* bullet = new Bullet();
	Vector2D firingPos = mPosition + Vector2D(cos(mRotation * PI / 180.0), sin(mRotation * PI / 180.0)) * mShipLength;
	bullet->SetPosition(firingPos);
	float bulletSpeed = 200.0f;
	Vector2D bulletVelocity = (firingPos - mPosition).Normalised() * bulletSpeed;
	bullet->SetVelocity(bulletVelocity);

	mWorld->AddBullet(bullet);
}

void SpaceShip::OnCollision(WorldObject* collidingObject)
{
	Kill();
}

void SpaceShip::Kill()
{
	WorldObject::Kill();
	int numPieces = 64 + rand() % 64;
	GenerateDebris(numPieces);
	FireBullet();
}

void SpaceShip::GenerateDebris(int numPieces) const
{
	std::vector<Debris*> generatedDebris;
	const float shipArea = mShipWidth * mShipLength / 2.0f;
	for (int i = 0; i < numPieces; i++)
	{
		// determine length scale of this debris
		float randomVariationFactor = 0.25f + ((rand() % 15) / 10.0f); // 0.25 - 1.75
		float debrisArea = shipArea / numPieces * randomVariationFactor;
		float lengthScale = sqrt(debrisArea);
		Debris* newDebris = new Debris(lengthScale);

		float debrisMass = mMass * debrisArea / shipArea;
		newDebris->SetMass(debrisMass);

		// equally spread around centre at random distance
		float distance = rand() % (int)(mShipWidth / 2.0f);
		double angle = 2.0 * PI * (double)i / (double)numPieces;
		Vector2D offsetPos = Vector2D(cos(angle), sin(angle)) * distance;
		Vector2D debrisPos = mPosition + offsetPos;
		newDebris->SetPosition(debrisPos);

		// same velocity as ship but with explosion force added
		newDebris->SetVelocity(mVelocity);
		// apply explosion force, more pieces -> less force on each
		float explosionForceFactor = (100.0f + rand() % 200) / numPieces;
		Vector2D force = (debrisPos - mPosition) * explosionForceFactor;
		newDebris->AddForce(force);

		generatedDebris.push_back(newDebris);
	}

	// add the debris to the world
	mWorld->AddDebris(generatedDebris);
}

void SpaceShip::UpdatePhysics(const float deltaTime)
{
	WorldObject::UpdatePhysics(deltaTime);
	double radians = atan2(mVelocity.Y, mVelocity.X);
	double degrees = radians * (180.0 / PI);
	mRotation = (float)degrees;
}

void SpaceShip::Draw(sf::RenderWindow* drawWindow)
{
	WorldObject::Draw(drawWindow);

	drawWindow->draw(&mTrail[0], mTrail.size(), sf::LineStrip);

	bool debugDrawCollisionCircle = false;
	if (debugDrawCollisionCircle)
	{
		sf::CircleShape collisionCircle(mCollisionRadius, 30);
		collisionCircle.setOrigin(mCollisionRadius, mCollisionRadius);
		collisionCircle.setFillColor(sf::Color::Transparent);
		collisionCircle.setOutlineThickness(1.0f);
		collisionCircle.setOutlineColor(sf::Color::White);
		collisionCircle.setPosition(mModel->getPosition());
		collisionCircle.setRotation(mModel->getRotation());
		drawWindow->draw(collisionCircle);
	}
}

sf::Shape* SpaceShip::GenerateModel() const
{
	sf::ConvexShape* shipModel = new sf::ConvexShape();

	shipModel->setPointCount(3);
	shipModel->setPoint(0, sf::Vector2f(0.f, 0.f));
	shipModel->setPoint(1, sf::Vector2f(0.f, mShipWidth));
	shipModel->setPoint(2, sf::Vector2f(mShipLength, mShipWidth / 2.0f));

	// set origin 
	sf::Vector2f centroid(mShipLength / 3.0f, mShipWidth / 2.0f);
	shipModel->setOrigin(centroid);

	shipModel->setFillColor(sf::Color::Black);
	shipModel->setOutlineThickness(1.0f);
	shipModel->setOutlineColor(sf::Color(255, 255, 255));

	return shipModel;
}

void SpaceShip::UpdateVisual()
{
	WorldObject::UpdateVisual();

	// destroy first element in trail and add current position to the end
	if (mTrail.size() >= mMaxNumTrailVertices)
	{
		mTrail.erase(mTrail.begin());
	}
	Vector2D newTrailPos = mPosition - mVelocity.Normalised() * mShipLength / 3.0f;
	sf::Vertex newVertex(sf::Vector2f(newTrailPos.X, newTrailPos.Y));
	mTrail.push_back(newVertex);
}
