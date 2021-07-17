/*
** By Kevin Pruvost, May 2020
** File description:
** RenderWindow class.
*/

#pragma once

// Project includes
#include "IZappyRenderWindow.hpp"
#include "BottomButton.hpp"
#include "InterfaceObject.hpp"
#include "InterfaceTextObject.hpp"
#include "Cursor.hpp"
#include "Floor.hpp"
#include "Mob.hpp"

/**
 * @brief Inherits from IZappyRenderWindow.
 * ZappyRenderWindow's main purpose is to automatize sprite progressive moves & animations.
 */
class ZappyRenderWindow : virtual public IZappyRenderWindow
{
public:
	ZappyRenderWindow(const sf::VideoMode & videoMode, const std::string & name,
					  sf::Uint32 style);
	~ZappyRenderWindow();

	using sf::RenderWindow::draw;
	/**
	 * @brief sf::RenderWindow::draw() has been modified to take additional
	 * sf::Drawable types made in this project, like the Object class that inherits
	 * many other children classes that need a special treatment in the draw() process.
	 * @param obj
	 */
	void draw(InterfaceTextObject & obj);
	void draw(TextObject & obj);
	void draw(Object & obj);
	void draw(InterfaceObject & obj);
	void draw(Cursor & cursor);
	void draw(Floor & obj);
	void draw(Mob & obj);
	void draw(BottomButton & obj);
	void draw(KVector<BottomButton> & obj);
	void zoom(float zoomMultiplier);
	float getActualZoom();
public:
	float actualZoom = 1;
};