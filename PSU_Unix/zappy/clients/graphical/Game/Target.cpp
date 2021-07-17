/*
** By Kevin Pruvost, June 2020
** File description:
** Target class.
*/

#include "Target.hpp"

Target::Target()
{

}

Target::Target(const Cocoon & cocoon)
{
    *this = cocoon;
}

Target::Target(const Mob & cocoon)
{
    *this = cocoon;
}

Target::Target(const Floor & cocoon)
{
    *this = cocoon;
}

Target::Target(const Object * cocoon)
{
    *this = cocoon;
}

Target::~Target()
{

}

Target & Target::operator=(const Cocoon & cocoon)
{
    objectIdentity = cocoon.objectIdentity;
    pos = cocoon.pos;
    id = cocoon.id;
    return *this;
}

Target & Target::operator=(const Mob & mob)
{
    objectIdentity = mob.objectIdentity;
    pos = mob.pos;
    id = mob.id;
    return *this;
}

Target & Target::operator=(const Floor & floor)
{
    objectIdentity = floor.objectIdentity;
    pos = floor.pos;
    id = 0;
    return *this;
}

Target & Target::operator=(const Object * obj)
{
    if (obj->objectIdentity == Object::ObjectIdentity::Egg)
        *this = *((Cocoon *)obj);
    else if (obj->objectIdentity == Object::ObjectIdentity::Mob)
        *this = *((Mob *)obj);
    else if (obj->objectIdentity == Object::ObjectIdentity::Floor)
        *this = *((Floor *)obj);
    return *this;
}

bool Target::operator==(const Cocoon & cocoon)
{
    return id == cocoon.id && pos == cocoon.pos && objectIdentity == cocoon.objectIdentity;
}

bool Target::operator==(const Mob & mob)
{
    return id == mob.id && objectIdentity == mob.objectIdentity;
}

bool Target::operator==(const Floor & floor)
{
    return pos == floor.pos && objectIdentity == floor.objectIdentity;
}

Object * Target::get(const KVector<Mob> & players, const KVector<Cocoon> & eggs, const KVector<Floor> & tiles)
{
    if (objectIdentity == Object::ObjectIdentity::Mob)
    {
        for (auto & player : players)
            if (*this == player)
                return (Object *)&player;
    }
    else if (objectIdentity == Object::ObjectIdentity::Egg)
    {
        for (auto & player : eggs)
            if (*this == player)
                return (Object *)&player;
    }
    else if (objectIdentity == Object::ObjectIdentity::Floor)
    {
        for (auto & player : tiles)
            if (*this == player)
                return (Object *)&player;
    }
    return nullptr;
}