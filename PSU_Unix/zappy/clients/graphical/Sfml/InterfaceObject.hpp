/*
** By Kevin Pruvost, June 2020
** File description:
** InterfaceObject class.
*/

#pragma once

// Project includes
#include "Object.hpp"

/**
 * @brief Object aimed to be considered as a UI part. Its position and scale
 * does not change with the zoom or position of the camera.
 */
class InterfaceObject : public Object
{
public:
	using Object::Object;
	InterfaceObject(Constants::TextureId id, int x, int y);
	InterfaceObject(Constants::TextureId id, const sf::Vector2f & vec);
	~InterfaceObject();

	/**
	 * @brief Sets the interface position.
	 * @param x
	 * @param y
	 */
	void setInterfacePosition(int x, int y);
	/**
	 * @brief Sets the origin to the center of the sprite.
	 */
	void centerObject();

private:
};