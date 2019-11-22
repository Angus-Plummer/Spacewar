#include "SpaceShip.h"
#include "../GameInstance.h"

SpaceShip::SpaceShip()
	: WorldObject()
	, mAmmo(0)
	, mHealth(0.0f)
	, mIsAlive(true)
{
	mIsPhysicsEnabled = true;
	SetupVisual();
}

void SpaceShip::Kill()
{
	mIsAlive = false;
	// explosion
}

bool SpaceShip::IsAlive()
{
	return mIsAlive;
}

void SpaceShip::Update(const float deltaTime)
{
	WorldObject::Update(deltaTime);
}

void SpaceShip::Draw(sf::RenderWindow* drawWindow)
{
	WorldObject::Draw(drawWindow);

	drawWindow->draw(&mTrail[0], mTrail.size(), sf::LineStrip);
}

sf::ConvexShape* SpaceShip::GenerateModel() const
{
	sf::ConvexShape* shipModel = new sf::ConvexShape();

	float width = 10.0f; //rand() % 10 + 5;
	float length = 15.0f; //rand() % 10 + 10;
	shipModel->setPointCount(3);
	shipModel->setPoint(0, sf::Vector2f(0.f, 0.f));
	shipModel->setPoint(1, sf::Vector2f(0.f, width));
	shipModel->setPoint(2, sf::Vector2f(length, width / 2.0f));

	// set origin 
	sf::Vector2f centroid(length / 3.0f, width / 2.0f);
	shipModel->setOrigin(centroid);

	shipModel->setFillColor(sf::Color::White);
	shipModel->setOutlineThickness(-1.0f); // outline from edge towards centre
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
	sf::Vertex newVertex(sf::Vector2f(mPosition.X, mPosition.Y));
	mTrail.push_back(newVertex);
}

std::vector<sf::Shape*> SpaceShip::GenerateDebris()
{
	return std::vector<sf::Shape*>();
}

void SpaceShip::UpdatePhysics(const float deltaTime)
{
	WorldObject::UpdatePhysics(deltaTime);
	double radians = atan2(mVelocity.Y, mVelocity.X);
	double degrees = radians * (180.0 / 3.141592653589793238463);
	mRotation = (float)degrees;
}
