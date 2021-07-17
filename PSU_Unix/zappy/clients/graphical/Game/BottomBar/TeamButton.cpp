/*
** By Kevin Pruvost, June 2020
** File description:
** TeamButton class.
*/

#include "TeamButton.hpp"

TeamButton::TeamButton(const std::string & str, sf::Color teamColor, int x, int y)
    : BottomButton(Constants::TextureId::BOTTOM_TEAMS_SQUARE, x, y)
{
    buttonId = 't';
    _textObjects.emplace_back(Constants::FontId::STARCRAFT_FONT, str);
    _textObjects[0].setFillColor(teamColor);
    _textObjects[0].pos.x = 10;
    _textObjects[0].pos.y = 20;
}

TeamButton::~TeamButton()
{

}