/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RoundObject
*/

#include "RoundObject.hpp"

RoundObject::RoundObject(GameObject *parent)
: SphericObject(parent) {}
RoundObject::RoundObject(const Vector2 &pos, size_t radius, GameObject *parent)
: SphericObject(pos, {double(radius), double(radius), 0}, parent) {}
RoundObject::RoundObject(const Vector2 &pos, const Vector2 radiuses, GameObject *parent)
: SphericObject(pos, radiuses, parent) {}
RoundObject::RoundObject(const Vector2 &pos, const Vector2 radiuses, double angle, GameObject *parent)
: SphericObject(pos, radiuses, {0, 0, angle}, parent) {}

RoundObject::~RoundObject()
{
}
