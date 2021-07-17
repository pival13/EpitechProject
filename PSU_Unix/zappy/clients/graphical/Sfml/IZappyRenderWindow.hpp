/*
** By Kevin Pruvost, June 2020
** File description:
** IZappyRenderWindow class.
*/

#pragma once

// Project includes
#include "SfmlIncludes.hpp"

/**
 * @brief ZappyRenderWindow Interface.
 */
class IZappyRenderWindow : virtual public sf::RenderWindow
{
public:
	virtual ~IZappyRenderWindow() = default;

	/**
	 * @brief Used to get the render window actual zoom.
	 * @return float
	 */
	virtual float getActualZoom() = 0;
};