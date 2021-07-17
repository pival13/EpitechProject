/*
** By Kevin Pruvost, June 2020
** File description:
** InterfaceTextObject class.
*/

#include "InterfaceTextObject.hpp"

InterfaceTextObject::InterfaceTextObject(Constants::FontId id, const std::string & str, int x, int y)
    : TextObject(id, str, x, y)
{
    pos.x = x;
    pos.y = y;
}

InterfaceTextObject::InterfaceTextObject(Constants::FontId id, const std::string & str, const sf::Vector2f & vec)
    : InterfaceTextObject(id, str, vec.x, vec.y)
{
}

InterfaceTextObject::~InterfaceTextObject()
{

}

void InterfaceTextObject::setInterfacePosition(int x, int y)
{
    pos.x = x;
    pos.y = y;
}