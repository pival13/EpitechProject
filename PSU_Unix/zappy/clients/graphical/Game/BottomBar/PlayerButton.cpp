/*
** By Kevin Pruvost, June 2020
** File description:
** PlayerButton class.
*/

#include "PlayerButton.hpp"

PlayerButton::PlayerButton(int playerId, Constants::TextureId textureId, int x, int y)
    : BottomButton(Constants::TextureId::BOTTOM_PLAYER_SQUARE, x, y)
{
    _playerId = playerId;
    buttonId = 'p';
    _objects.emplace_back(textureId);
    _objects[0].pos.x = 0;
    _objects[0].pos.y = 0;
}

PlayerButton::~PlayerButton()
{

}