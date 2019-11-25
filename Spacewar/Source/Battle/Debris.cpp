#include "Debris.h"

Debris::Debris()
	: WorldObject()
	, mSize(2.0f)
{
	mCollisionRadius = mSize;
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	mIsWrapAround = false;
	SetupVisual();
}

Debris::Debris(float size)
	: WorldObject()
	, mSize(size)
{
	mCollisionRadius = mSize;
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	mIsWrapAround = false;
	SetupVisual();
}

void Debris::Kill()
{
	Destroy();
}

void Debris::OnCollision(WorldObject* collidingObject)
{
	Kill(); // kill self
}

void Debris::UpdatePhysics(const float deltaTime)
{
	WorldObject::UpdatePhysics(deltaTime);
}

sf::Shape * Debris::GenerateModel() const
{
	int numSides = 3 + rand() % 3;
	sf::CircleShape* debrisModel = new sf::CircleShape(mSize, numSides);

	// set origin 
	sf::Vector2f centre(mSize, mSize);
	debrisModel->setOrigin(centre);

	debrisModel->setFillColor(sf::Color::Black);
	debrisModel->setOutlineThickness(1.0f);
	debrisModel->setOutlineColor(mOutlineColor.AsSFMLColor());

	return debrisModel;
}

void Debris::SetupVisual()
{
	mOutlineColor.R = 255.0f;
	mOutlineColor.G = 50.0f + rand() % 100;
	mOutlineColor.B = 0.0f;
	mOutlineColor.A = 255.0f;

	WorldObject::SetupVisual();
}

void Debris::UpdateVisual(const float deltaTime)
{
	WorldObject::UpdateVisual(deltaTime);
	
	// slowly change color
	sf::Color color = mModel->getOutlineColor();
	float colorDecayTime = 20.0f; // time for 1/e
	float fadeTime = 1.0f;

	auto exponentialTrend = [deltaTime](float currentVal, float targetVal, float timeFactor) 
	{
		float newVal = targetVal + (currentVal - targetVal) * exp(-deltaTime / timeFactor);
		return newVal;
	};


	mOutlineColor.R = exponentialTrend(mOutlineColor.R, 255.0f, colorDecayTime);
	mOutlineColor.G = exponentialTrend(mOutlineColor.G, 200.0f, colorDecayTime);
	mOutlineColor.B = exponentialTrend(mOutlineColor.B, 200.0f, colorDecayTime);
	mOutlineColor.A = exponentialTrend(mOutlineColor.A, 200.0f, fadeTime);
	
	mModel->setOutlineColor(mOutlineColor.AsSFMLColor()); // this operation is expensive!
	
}
