#include "Bullet.h"
#include "SpaceShip.h"

Bullet::Bullet()
	: WorldObject()
{
	mIsPhysicsEnabled = true;
	mIsCollisionEnabled = true;
	mCollisionRadius = 3.0f;
	SetupVisual();
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

void Bullet::Draw(sf::RenderWindow* drawWindow)
{
	WorldObject::Draw(drawWindow);
	drawWindow->draw(&mTrail[0], mTrail.size(), sf::LineStrip);
}

sf::Shape* Bullet::GenerateModel() const
{
	//float width = 3.0f;
	//sf::RectangleShape* bulletModel = new sf::RectangleShape(sf::Vector2f(mCollisionRadius, width));
	//bulletModel->setOrigin(mCollisionRadius / 2.0f, width /2.0f);

	sf::CircleShape* bulletModel = new sf::CircleShape(mCollisionRadius, 30);
	bulletModel->setOrigin(mCollisionRadius, mCollisionRadius);

	bulletModel->setFillColor(sf::Color::Red);
	//bulletModel->setOutlineThickness(1.0f);
	//bulletModel->setOutlineColor(sf::Color::Red);

	return bulletModel;
}

void Bullet::UpdateVisual()
{
	WorldObject::UpdateVisual();

	// destroy first element in trail and add current position to the end
	if (mTrail.size() >= mMaxNumTrailVertices)
	{
		mTrail.erase(mTrail.begin());
	}
	Vector2D newTrailPos = mPosition;
	sf::Vertex newVertex(sf::Vector2f(newTrailPos.X, newTrailPos.Y), sf::Color::Red);
	mTrail.push_back(newVertex);
}
