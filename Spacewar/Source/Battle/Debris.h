#pragma once
#include "WorldObject.h"

struct ColorF
{
	float R;
	float G;
	float B;
	float A;

	sf::Color AsSFMLColor() const
	{
		return sf::Color((int)R, (int)G, (int)B, (int)A);
	}
};

class Debris : public WorldObject
{
public:
	Debris();
	Debris(float size);

	virtual void Kill() override;

	virtual void OnCollision(WorldObject* collidingObject) override;

protected:
	virtual void UpdatePhysics(const float deltaTime) override;

	// Drawable Implementation
protected:
	float mSize; // characteristic length scale
	virtual sf::Shape* GenerateModel() const override;
	ColorF mOutlineColor;
	virtual void SetupVisual() override;
	virtual void UpdateVisual(const float deltaTime) override;
};