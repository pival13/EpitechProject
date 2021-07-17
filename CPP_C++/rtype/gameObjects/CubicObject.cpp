/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** CubicObject
*/

#include "CubicObject.hpp"

CubicObject::CubicObject(GameObject *parent)
: CubicObject({0, 0, 0}, 1, parent) {}
CubicObject::CubicObject(const Vector3 &origin, size_t size, GameObject *parent)
: CubicObject(origin, {double(size), double(size), double(size)}, parent) {}
CubicObject::CubicObject(const Vector3 &origin, const Vector3 &sizes, GameObject *parent)
: GameObject(Transform(origin, sizes), parent), collider(*this, sizes)
{}

CubicObject::CubicObject(const Vector3 &origin, const Vector3 &sizes, const Vector3 &angle, GameObject *parent)
: GameObject(Transform(origin, sizes, {0.5,0.5,0.5}, angle), parent), collider(*this, sizes)
{}

CubicObject::~CubicObject()
{
}
