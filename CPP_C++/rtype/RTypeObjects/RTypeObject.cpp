/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RTypeObject
*/

#include "RTypeObject.hpp"
#include "game/RType.hpp"
/*
RTypeObject::RTypeObject(GameObject *)
{
}
*/
RTypeObject::~RTypeObject()
{
}

void RTypeObject::update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy, RTypeCreate)
{
    move(direction * double(rt.deltaTime.count()) / 1000);
    for (Collider *c : colliders)
        if (&c->gameObject == this)
            c->checkBoundary(colliders);
}