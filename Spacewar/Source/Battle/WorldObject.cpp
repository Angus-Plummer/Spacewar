#include "WorldObject.h"
#include "../GameInstance.h"
#include "World.h"

WorldObject::WorldObject()
	: mPosition()
	, mVelocity()
	, mRotation(0.0f)
	, mAngularVelocity(0.0f)
	, mWorld(nullptr)
	, mIsPhysicsEnabled(false)
	, mIsCollisionEnabled(false)
	, mModel(nullptr)
	, mMass(1.0f)
	, mCollisionRadius(0.0f)
	, mIsAlive(true)
	, mIsPendingDestroy(false)
	, mIsWrapAround(true)
	, mIsFaceMovementDirection(false)
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
	UpdateVisual(deltaTime);

	if (!mWorld->IsWithinBounds(mPosition))
	{
		OnLeaveWorldBounds();
	}
}

void WorldObject::SetWorld(World * world)
{
	mWorld = world;
}

void WorldObject::Destroy()
{
	mIsPendingDestroy = true;
	SetIsDrawingEnabled(false);
}

bool WorldObject::IsPendingDestroy() const
{
	return mIsPendingDestroy;
}

void WorldObject::Kill()
{
	mIsAlive = false;
}

bool WorldObject::IsAlive() const
{
	return mIsAlive;
}

Vector2D WorldObject::ForwardVector() const
{
	return Vector2D((float)cos(mRotation * PI / 180.0), (float)sin(mRotation * PI / 180.0));
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

void WorldObject::SetAngularVelocity(float newAngularVel)
{
	mAngularVelocity = newAngularVel;
}

float WorldObject::GetAngularVelocity() const
{
	return mAngularVelocity;
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

void WorldObject::SetIsFaceMovementDirection(bool isFaceMoveDirection)
{
	mIsFaceMovementDirection = isFaceMoveDirection;
}

bool WorldObject::GetIsFaceMovementDirection() const
{
	return mIsFaceMovementDirection;
}

void WorldObject::OnCollision(WorldObject* collidingObject)
{

}

void WorldObject::OnLeaveWorldBounds()
{
	if (mIsWrapAround)
	{
		mPosition = mWorld->WrapAround(mPosition);
	}
}

void WorldObject::UpdatePhysics(const float deltaTime)
{
	mVelocity += mPendingForce / mMass * deltaTime;
	mPendingForce = Vector2D();
	mPosition += mVelocity * deltaTime;

	if (mIsFaceMovementDirection)
	{
		double radians = atan2(mVelocity.Y, mVelocity.X);
		double degrees = radians * (180.0 / PI);
		mRotation = (float)degrees;
	}
	else
	{
		mRotation += mAngularVelocity * deltaTime;
		mRotation = fmodf(mRotation, 360.0f);
	}
}

void WorldObject::Draw(sf::RenderWindow* drawWindow)
{
	if (mModel)
	{
		drawWindow->draw(*mModel);	
	}
}

void WorldObject::UpdateVisual(const float deltaTime)
{
	// set the underlying drawn shape's properties to those of the game object
	if (mModel)
	{
		Vector2D screenPosition = mWorld->WorldToScreenPos(mPosition);
		mModel->setPosition(screenPosition.X, screenPosition.Y);
		mModel->setRotation(mRotation);
	}
}

void WorldObject::SetupVisual()
{
	mModel = GenerateModel();
}
