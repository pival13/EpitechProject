/*
** By Kevin Pruvost, May 2020
** File description:
** Cursor class.
*/

#pragma once

// Project includes
#include "InterfaceObject.hpp"
#include "IZappyRenderWindow.hpp"

// C++ includes
#include <memory>

/**
 * @brief Used to draw shadows upon objects it is aiming and to indicate where
 * the sf::Mouse events are aiming.
 */
class Cursor : virtual public InterfaceObject
{
public:
	Cursor(Constants::TextureId tID);
	~Cursor();

	/**
	 * @brief Updates the position on the window.
	 * @param window
	 */
	void updatePosition(IZappyRenderWindow & window);
	/**
	 * @brief Gets the aimed object by the cursor.
	 * @return std::unique_ptr<Object>*
	 */
	std::unique_ptr<Object> * getHighlight();
	/**
	 * @brief Creates a shadow on the object to make a highlight effect.
	 * @param object
	 * @return true
	 * @return false
	 */
	bool highlightObject(Object & object);
	/**
	 * @brief Cancels highlighting.
	 */
	void resetHighlight();
	/**
	 * @brief Refreshes which object the cursor is highlighting.
	 * @return true
	 * @return false
	 */
	bool refreshHighlight();

	/**
	 * @brief Animates a pressed click.
	 */
	void clickAnimation();
	/**
	 * @brief Animates a released click.
	 */
	void noClickAnimation();

private:
	bool _clickAnimationState = false;

public:
	/**
	 * @brief Contains a pointer to the highlighted object.
	 */
	Object * pointedObject = nullptr;

private:
	std::unique_ptr<Object> _highlight;
	bool _highlightReleased = true;
};