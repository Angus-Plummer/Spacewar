#include "SpaceShip.h"
#include "../GameInstance.h"
#include "Debris.h"
#include "Bullet.h"
#include "World.h"

SpaceShip::SpaceShip()
	: WorldObject()
	, mAmmo(100)
	, mHealth(0.0f)
	, mFuel(100.0f)
	, mShipWidth(20.f)
	, mShipLength(30.0f)
	, mIsThrustersEnabled(false)
	, mThrusterImpulse(100.0f)
	, mManualRotationRate(180.0f)
{
	mIsFaceMovementDirection = true;
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
	if (mAmmo > 0)
	{
		mAmmo--;
		
		// create bullet and add to world
		Bullet* bullet = new Bullet();
		Vector2D firingPos = mPosition + ForwardVector() * mShipLength * 2.0f / 3.0f;
		bullet->SetPosition(firingPos);
		float bulletSpeed = 250.0f;
		Vector2D bulletVelocity = (firingPos - mPosition).Normalised() * bulletSpeed;
		bulletVelocity += ForwardVector() * std::max(0.0f, ForwardVector().DotProd(mVelocity));
		bullet->SetVelocity(bulletVelocity);

		mWorld->AddBullet(bullet);
	}
}

void SpaceShip::FireThrusters(const float deltaTime)
{
	float fuelUsageRate = 1.0f;
	Vector2D thrusterForce = ForwardVector() * mThrusterImpulse;
	AddForce(thrusterForce);
	mFuel -= fuelUsageRate * deltaTime;
	if (mFuel < 0.0f)
	{
		mFuel = 0.0f;
		DisableThrusters();
	}
}

void SpaceShip::EnableThrusters()
{
	if (mFuel > 0)
	{
		mIsThrustersEnabled = true;
	}
}

void SpaceShip::DisableThrusters()
{
	mIsThrustersEnabled = false;
}

void SpaceShip::StartManualRotation(TurningDirection direction)
{
	float angularVelocity = mManualRotationRate * (direction == Clockwise ? 1.0f : -1.0f);
	SetAngularVelocity(angularVelocity);
}

void SpaceShip::StopManualRotation(TurningDirection direction)
{
	// if angular velocity is in same direction then stop it
	if (mAngularVelocity * (direction == Clockwise ? 1.0f : -1.0f) > 0.0f)
	{
		SetAngularVelocity(0.0f);
	}
}

void SpaceShip::OnCollision(WorldObject* collidingObject)
{
	Kill();
}

void SpaceShip::Kill()
{
	WorldObject::Kill();
	
	int numPieces = 32;
	GenerateDebris(numPieces);

	SetIsPhysicsEnabled(false);
	SetIsCollisionEnabled(false);
	SetIsDrawingEnabled(false);
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
		float distance = (float) (rand() % (int)(mShipWidth / 2.0f));
		float angle = 2.0f * PI * (float)i / (float)numPieces;
		Vector2D offsetPos = Vector2D(cos(angle), sin(angle)) * distance;
		Vector2D debrisPos = mPosition + offsetPos;
		newDebris->SetPosition(debrisPos);

		// same velocity as ship but with explosion force added
		newDebris->SetVelocity(mVelocity);
		// apply explosion force, more pieces -> less force on each
		float explosionForceFactor = (100.0f + rand() % 200) / numPieces;
		Vector2D force = (debrisPos - mPosition) * explosionForceFactor;
		newDebris->AddForce(force);

		float randomAngularVel = (-360.0f + rand() % 720) * 3.0f; // max 3 rotation per second
		newDebris->SetAngularVelocity(randomAngularVel);

		generatedDebris.push_back(newDebris);
	}

	// add the debris to the world
	mWorld->AddDebris(generatedDebris);
}

void SpaceShip::UpdatePhysics(const float deltaTime)
{
	if (mIsThrustersEnabled)
	{
		FireThrusters(deltaTime);
	}

	WorldObject::UpdatePhysics(deltaTime);
}

void SpaceShip::Draw(sf::RenderWindow* drawWindow)
{
	//drawWindow->draw(&mTrail[0], mTrail.size(), sf::LineStrip);

	WorldObject::Draw(drawWindow);

	if (mIsThrustersEnabled)
	{
		for (int i = 0; i < mThrustersModel.size(); i++)
		{
			sf::Shape* thrusterComponent = mThrustersModel[i];
			drawWindow->draw(*thrusterComponent);
		}
	}
	
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
	shipModel->setOutlineThickness(-1.0f);
	shipModel->setOutlineColor(sf::Color(255, 255, 255));

	return shipModel;
}

void SpaceShip::UpdateVisual(const float deltaTime)
{
	WorldObject::UpdateVisual(deltaTime);

	if (mIsThrustersEnabled)
	{
		// update thruster position
		for (int i = 0; i < mThrustersModel.size(); i++)
		{
			sf::Shape* thrusterComponent = mThrustersModel[i];
			Vector2D worldOrigin = mWorld->GetOrigin();
			Vector2D screenPosition = worldOrigin + mPosition;
			thrusterComponent->setPosition(screenPosition.X, screenPosition.Y);
			thrusterComponent->setRotation(mRotation);
		}
	}
}

std::vector<sf::Shape*> SpaceShip::GenerateThrustersModel()
{
	std::vector<sf::Shape*> thrustersModel;
	// three components to the thruster (concave shapes not allowed in SFML)
	sf::ConvexShape* leftThruster = new sf::ConvexShape(3);
	sf::ConvexShape* rightThruster = new sf::ConvexShape(3);
	sf::ConvexShape* centreThruster = new sf::ConvexShape(3);

	float mainThrusterLength = mShipLength / 2.5f;
	float sideThrusterLength = mainThrusterLength / 2.0f;
	// left thruster
	leftThruster->setPoint(0, sf::Vector2f(0.f, 0.0f));
	leftThruster->setPoint(1, sf::Vector2f(-sideThrusterLength, mShipWidth / 4.0f));
	leftThruster->setPoint(2, sf::Vector2f(0.0f, mShipWidth / 2.0f));
	// right thruster
	rightThruster->setPoint(0, sf::Vector2f(0.f, mShipWidth / 2.0f));
	rightThruster->setPoint(1, sf::Vector2f(-sideThrusterLength, mShipWidth * 3.0f / 4.0f));
	rightThruster->setPoint(2, sf::Vector2f(0.0f, mShipWidth));
	// centre thruster
	centreThruster->setPoint(0, sf::Vector2f(0.f, mShipWidth / 4.0f));
	centreThruster->setPoint(1, sf::Vector2f(-mainThrusterLength, mShipWidth / 2.0f));
	centreThruster->setPoint(2, sf::Vector2f(0.0f, mShipWidth * 3.0f / 4.0f));

	thrustersModel.push_back(leftThruster);
	thrustersModel.push_back(rightThruster);
	thrustersModel.push_back(centreThruster);

	// set their origins
	sf::Vector2f centroid(mShipLength / 3.0f, mShipWidth / 2.0f);

	for (int i = 0; i < thrustersModel.size(); i++)
	{
		sf::Shape* thrusterComponent = thrustersModel[i];
		thrusterComponent->setOrigin(centroid);
		thrusterComponent->setFillColor(sf::Color::Black);
		thrusterComponent->setOutlineThickness(-1.0f);
		thrusterComponent->setOutlineColor(sf::Color::White);
	}

	return thrustersModel;
}

void SpaceShip::SetupVisual()
{
	WorldObject::SetupVisual();

	mThrustersModel = GenerateThrustersModel();
}
