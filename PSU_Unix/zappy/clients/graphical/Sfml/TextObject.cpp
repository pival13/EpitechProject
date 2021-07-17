/*
** By Kevin Pruvost, June 2020
** File description:
** TextObject class.
*/

#include "TextObject.hpp"

TextObject::TextObject(Constants::FontId id, const std::string & str)
    : text { str }
    , font { &fontBase[id] }
    , fontId { id }
{
    setFillColor({159, 48, 255});
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(0.5);
    setString(str);
    setFont(*font);
    setCharacterSize(18);
}

TextObject::TextObject(Constants::FontId id, const std::string & str, int x, int y)
    : TextObject(id, str)
{
    pos.x = x;
    pos.y = y;
}

TextObject::TextObject(Constants::FontId id, const std::string & str, const sf::Vector2f & vec)
    : TextObject(id, str, vec.x, vec.y)
{
}

TextObject::~TextObject()
{

}