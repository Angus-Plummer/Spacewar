#pragma once
#include <SFML/Graphics.hpp>

//interface for objects drawn on the screen
class Drawable
{
public:
	virtual void Draw(sf::RenderWindow* drawWindow) = 0;
};