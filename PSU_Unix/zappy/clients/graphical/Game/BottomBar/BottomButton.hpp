/*
** By Kevin Pruvost, June 2020
** File description:
** BottomButton class.
*/

#pragma once

// Project includes
#include "InterfaceObject.hpp"

/**
 * @brief Used for the bottom bar, to display players and teams.
 */
class BottomButton : public InterfaceObject
{
public:
	BottomButton(Constants::TextureId textureId, int x = 0, int y = 0);
	~BottomButton();

	/**
	 * @brief Sets the string of the first _textObjects.
	 * @param str
	 */
	void setString(const std::string & str);
	/**
	 * @brief Gets the string of the first _textObjects.
	 * @return std::string
	 */
	std::string getString();
	/**
	 * @brief Sets the icon texture on the first _objects.
	 * @param textureId
	 */
	void setIconTexture(Constants::TextureId textureId);

public:
	KVector<Object> _objects;
	char buttonId;
	int _playerId = 0;
};