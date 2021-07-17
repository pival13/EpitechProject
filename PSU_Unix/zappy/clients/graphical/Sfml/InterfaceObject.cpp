/*
** By Kevin Pruvost, June 2020
** File description:
** InterfaceObject class.
*/

#include "InterfaceObject.hpp"

InterfaceObject::InterfaceObject(Constants::TextureId id, int x, int y)
    : Object(id, x, y)
{
    setInterfacePosition(x, y);
    objectIdentity = ObjectIdentity::Interface;
    setOrigin(0, 0);
}

InterfaceObject::InterfaceObject(Constants::TextureId id, const sf::Vector2f & vec)
    : InterfaceObject(id, vec.x, vec.y)
{
}

InterfaceObject::~InterfaceObject()
{
}

void InterfaceObject::setInterfacePosition(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

void InterfaceObject::centerObject()
{
    setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
}