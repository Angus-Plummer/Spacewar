#include "SpaceShip.h"
#include "../GameInstance.h"
#include "Debris.h"

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

void SpaceShip::OnCollision()
{
	Kill();
}

std::vector<Debris*> SpaceShip::GenerateDebris(int numPieces) const
{
	std::vector<Debris*> generatedDebris;
	float shipArea = mShipWidth * mShipLength / 2.0f;
	float averageAreaOfRemainingDebris = shipArea / numPieces;
	for (int i = 0; i < numPieces; i++)
	{
		float randomVariationFactor = (1.0f - (5 - rand() % 10) / 10.0f); // 0.5 - 1.5
		float debrisArea = averageAreaOfRemainingDebris *randomVariationFactor;
		averageAreaOfRemainingDebris += (averageAreaOfRemainingDebris - debrisArea) / (numPieces - i);
		float lengthScale = sqrt(debrisArea);
		Debris* newDebris = new Debris(lengthScale);

		float debrisMass = mMass * debrisArea / shipArea;
		newDebris->SetMass(debrisMass);

		// position
		float distance = rand() % (int)(mShipWidth / 2.0f);
		double angle = 2.0 * 3.141592653589793238463 * (double)i / (double)numPieces;
		Vector2D offsetPos = Vector2D(cos(angle), sin(angle)) * distance;
		Vector2D debrisPos = mPosition + offsetPos;
		float explosionForceFactor = 200.0f / numPieces;
		Vector2D force = (debrisPos - mPosition) * explosionForceFactor;
		newDebris->AddForce(force);
		newDebris->SetVelocity(mVelocity);
		newDebris->SetPosition(debrisPos);
		generatedDebris.push_back(newDebris);
	}
	return generatedDebris;
}

void SpaceShip::UpdatePhysics(const float deltaTime)
{
	WorldObject::UpdatePhysics(deltaTime);
	double radians = atan2(mVelocity.Y, mVelocity.X);
	double degrees = radians * (180.0 / 3.141592653589793238463);
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
