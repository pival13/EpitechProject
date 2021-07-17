/*
** By Kevin Pruvost, June 2020
** File description:
** InterfaceTextObject class.
*/

#pragma once

// Project includes
#include "TextObject.hpp"

/**
 * @brief TextObject aimed to be considered as a UI part. Its position and scale
 * does not change with the zoom or position of the camera.
 */
class InterfaceTextObject : virtual public TextObject
{
public:
	InterfaceTextObject(Constants::FontId id, const std::string & string, int x, int y);
	InterfaceTextObject(Constants::FontId id, const std::string & string, const sf::Vector2f & vec);
	~InterfaceTextObject();

	void setInterfacePosition(int x, int y);

private:
};