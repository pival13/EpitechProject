/*
** By Kevin Pruvost, May 2020
** File description:
** Cocoon class.
*/

#include "Cocoon.hpp"

Cocoon::Cocoon(int x, int y, int iD, int playerIDD)
    : Mob(x, y, iD, 0)
    , playerId { playerIDD }
{
    objectIdentity = ObjectIdentity::Egg;
    level = 0;
    changeTexture(textureByLevel.at(level));
    animate(AnimateOptions::Loop, 0.5, 0);
}

Cocoon::Cocoon(const sf::Vector2f & vec, int iD, int playerIDD)
    : Cocoon(vec.x, vec.y, iD, playerId)
{
}

Cocoon::~Cocoon()
{

}

bool Cocoon::operator==(const Cocoon & otherMob)
{
    return id == otherMob.id && pos == otherMob.pos && playerId == otherMob.playerId && level == otherMob.level;
}