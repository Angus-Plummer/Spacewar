#include "WorldObject.h"
#include "../GameInstance.h"

WorldObject::WorldObject()
	: mPosition()
	, mRotation(0.0f)
	, mWorld(nullptr)
	, mIsPhysicsEnabled(false)
	, mIsCollisionEnabled(false)
	, mModel(nullptr)
	, mMass(1.0f)
	, mCollisionRadius(0.0f)
	, mIsAlive(true)
{
}

WorldObject::~WorldObject()
{
	delete mModel;
}

void WorldObject::Update(const float deltaTime)
{
	if (mIsPhysicsEnabled)
	{
		UpdatePhysics(deltaTime);
	}
	UpdateVisual();

	// TODO : move this drawing out to another class which iterates through all Drawables and draws
	sf::RenderWindow* gameWindow = GameInstance::GetGameWindow();
	Draw(gameWindow);
}

void WorldObject::SetWorld(World * world)
{
	mWorld = world;
}

void WorldObject::Kill()
{
	mIsAlive = false;
}

bool WorldObject::IsAlive()
{
	return mIsAlive;
}

void WorldObject::SetPosition(const Vector2D& newPos)
{
	mPosition = newPos;
}

Vector2D WorldObject::GetPosition() const
{
	return mPosition;
}

void WorldObject::SetVelocity(const Vector2D & newVel)
{
	mVelocity = newVel;
}

Vector2D WorldObject::GetVelocity() const
{
	return mVelocity;
}

void WorldObject::SetMass(float newMass)
{
	mMass = newMass;
}

float WorldObject::GetMass() const
{
	return mMass;
}

void WorldObject::AddForce(const Vector2D & force)
{
	mPendingForce += force;
}

void WorldObject::SetRotation(float newRot)
{
	mRotation = newRot;
}

float WorldObject::GetRotation() const
{
	return mRotation;
}

void WorldObject::SetIsPhysicsEnabled(bool isEnablePhysics)
{
	mIsPhysicsEnabled = isEnablePhysics;
}

bool WorldObject::GetIsPhysicsEnabled() const
{
	return mIsPhysicsEnabled;
}

void WorldObject::SetIsCollisionEnabled(bool isCollisionEnabled)
{
	mIsCollisionEnabled = isCollisionEnabled;
}

bool WorldObject::GetIsCollisionEnabled() const
{
	return mIsCollisionEnabled;
}

void WorldObject::SetCollisionRadius(float radius)
{
	mCollisionRadius = radius;
}

float WorldObject::GetCollisionRadius() const
{
	return mCollisionRadius;
}

void WorldObject::OnCollision()
{

}

void WorldObject::UpdatePhysics(const float deltaTime)
{
	mVelocity += mPendingForce / mMass * deltaTime;
	mPendingForce = Vector2D();
	mPosition += mVelocity * deltaTime;
}

void WorldObject::Draw(sf::RenderWindow* drawWindow)
{
	if (drawWindow)
	{
		if (mModel)
		{
			drawWindow->draw(*mModel);	
		}
	}
}

void WorldObject::UpdateVisual()
{
	// set the underlying drawn shape's properties to those of the game object
	if (mModel)
	{
		mModel->setPosition(mPosition.X, mPosition.Y);
		mModel->setRotation(mRotation);
	}
}

void WorldObject::SetupVisual()
{
	mModel = GenerateModel();
}
