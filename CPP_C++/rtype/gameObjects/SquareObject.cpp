/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** SquareObject
*/

#include "SquareObject.hpp"

SquareObject::SquareObject(GameObject *parent)
: CubicObject(parent) {}
SquareObject::SquareObject(const Vector2 pos, size_t size, GameObject *parent)
: CubicObject(pos, {double(size), double(size), 0}, parent) {}
SquareObject::SquareObject(const Vector2 pos, const Vector2 sizes, GameObject *parent)
: CubicObject(pos, sizes, parent) {}
SquareObject::SquareObject(const Vector2 pos, const Vector2 sizes, double angle, GameObject *parent)
: CubicObject(pos, sizes, {0, 0, angle}, parent) {}

SquareObject::~SquareObject()
{
}
