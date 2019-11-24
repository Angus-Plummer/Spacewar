#include "Bullet.h"
#include "SpaceShip.h"
#include "World.h"

Bullet::Bullet()
	: WorldObject()
{
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	mCollisionRadius = 2.0f;
	SetupVisual();
	mTrail.resize(1);
}

void Bullet::Update(const float deltaTime)
{
	WorldObject::Update(deltaTime);
	if (!mIsAlive && mTrail.size() == 0)
	{
		Destroy();
	}
}

void Bullet::Kill()
{
	WorldObject::Kill();
	SetIsPhysicsEnabled(false);
	SetIsCollisionEnabled(false);
}

void Bullet::OnCollision(WorldObject* collidingObject)
{
	Kill();
}

void Bullet::UpdatePhysics(const float deltaTime)
{
	WorldObject::UpdatePhysics(deltaTime);
	double radians = atan2(mVelocity.Y, mVelocity.X);
	double degrees = radians * (180.0 / PI);
	mRotation = (float)degrees;
}

void Bullet::OnLeaveWorldBounds()
{
	WorldObject::OnLeaveWorldBounds();
	// split the trail
	mTrail.insert(mTrail.begin(), std::vector<sf::Vertex>());
}

void Bullet::Draw(sf::RenderWindow* drawWindow)
{
	if (mIsAlive)
	{
		WorldObject::Draw(drawWindow);
	}

	// draw all trail segments
	for (int i = 0; i < mTrail.size(); i++)
	{
		if(mTrail[i].size() > 0)
		drawWindow->draw(&mTrail[i][0], mTrail[i].size(), sf::LineStrip);
	}
}

sf::Shape* Bullet::GenerateModel() const
{
	sf::CircleShape* bulletModel = new sf::CircleShape(mCollisionRadius, 30);
	bulletModel->setOrigin(mCollisionRadius, mCollisionRadius);
	bulletModel->setFillColor(sf::Color::Red);

	return bulletModel;
}

void Bullet::UpdateVisual()
{
	WorldObject::UpdateVisual();

	// destroy last element in trail and add current position to the front
	int totalTrailLength = 0;
	for (int i = 0; i < mTrail.size(); i++)
	{
		totalTrailLength += (int) mTrail[i].size();
		for (int j = 0; j < mTrail[i].size(); j++)
		{
			sf::Vertex& vertex = mTrail[i][j];
			sf::Color& vertexColour = vertex.color;
			int fadeFactor = !mIsAlive ? 2 : 1;
			vertexColour.a = std::max(0, vertexColour.a - fadeFactor * 256 / mMaxNumTrailVertices);
			vertexColour.b = std::min(64, vertexColour.b + fadeFactor * 64 / mMaxNumTrailVertices);
			//vertexColour.g = std::min(255, vertexColour.g + fadeFactor * 256 / mMaxNumTrailVertices);
		}
	}
	if (totalTrailLength >= mMaxNumTrailVertices || !mIsAlive)
	{
		// destroy last vertex, if segment is now empty then destroy the segment
		std::vector<sf::Vertex>& lastTrailSegment = mTrail[mTrail.size() - 1];
		if (lastTrailSegment.size() > 0)
		{
			lastTrailSegment.pop_back();
		}
		if (lastTrailSegment.size() == 0)
		{
			mTrail.pop_back();
		}
	}

	if (mIsAlive)
	{
		// add new vertex at current position to front of first segment
		Vector2D newTrailPos = mWorld->WorldToScreenPos(mPosition);
		sf::Vertex newVertex(sf::Vector2f(newTrailPos.X, newTrailPos.Y), sf::Color::Red);
		mTrail[0].insert(mTrail[0].begin(), newVertex);
	}
}
