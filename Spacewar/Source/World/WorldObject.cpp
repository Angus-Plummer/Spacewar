#include "WorldObject.h"

WorldObject::WorldObject() 
	: mPosition()
	, mRotation(0.0f)
	, mShape(nullptr)
	, mIsPhysicsEnabled(false)
{
}

WorldObject::~WorldObject()
{
	delete mShape;
}

void WorldObject::Update(const float deltaTime)
{
	if (mIsPhysicsEnabled)
	{
		UpdatePhysics(deltaTime);
	}
	UpdateShape();
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

const sf::Shape* WorldObject::GetShape() const
{
	return mShape;
}

void WorldObject::UpdateShape()
{
	// set the underlying drawn shape's properties to those of the game object
	if (mShape)
	{
		mShape->setPosition(mPosition.X, mPosition.Y);
		mShape->setRotation(mRotation);
	}
}

void WorldObject::UpdatePhysics(const float deltaTime)
{
	mPosition += mVelocity * deltaTime;
}
