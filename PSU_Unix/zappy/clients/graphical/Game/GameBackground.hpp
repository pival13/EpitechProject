/*
** By Kevin Pruvost, May 2020
** File description:
** GameBackground class.
*/

#pragma once

// Project includes
#include "InterfaceObject.hpp"

/**
 * @brief Inherits from InterfaceObject and displays the background.
 */
class GameBackground : virtual public InterfaceObject
{
public:
	GameBackground(Constants::TextureId tId);
	~GameBackground();

	void moveBackground(int x, int y);
	void animateBackground(float speed);
	using InterfaceObject::setPosition;
	void setPosition(int x, int y);
	void setPosition();
	sf::Vector2f _basePos;
private:
};