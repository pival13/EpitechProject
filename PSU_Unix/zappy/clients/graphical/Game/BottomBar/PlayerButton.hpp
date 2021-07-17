/*
** By Kevin Pruvost, June 2020
** File description:
** PlayerButton class.
*/

#pragma once

// Project includes
#include "BottomButton.hpp"
#include "Cocoon.hpp"

/**
 * @brief Button designed to be clicked to get a player's informations and camera focus.
 */
class PlayerButton : public BottomButton
{
public:
	PlayerButton(int playerId, Constants::TextureId textureId, int x = 0, int y = 0);
	~PlayerButton();
};