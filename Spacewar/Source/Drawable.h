#pragma once
#include <SFML/Graphics.hpp>

//interface for objects drawn on the screen
class Drawable
{
public:
	virtual void Draw(sf::RenderWindow* drawWindow) = 0;

	virtual bool IsDrawingEnabled() const { return mIsDrawingEnabled; };
	virtual void SetIsDrawingEnabled(bool isDrawingEnabled) { mIsDrawingEnabled = isDrawingEnabled; };

protected:
	bool mIsDrawingEnabled = true;
};