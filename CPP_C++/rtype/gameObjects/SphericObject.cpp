/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** SphericObject
*/

#include "SphericObject.hpp"

SphericObject::SphericObject(GameObject *parent)
: SphericObject({0, 0, 0}, 1, parent) {}
SphericObject::SphericObject(const Vector3 &origin, size_t radius, GameObject *parent)
: SphericObject(origin, {double(radius), double(radius), double(radius)}, parent) {}
SphericObject::SphericObject(const Vector3 &origin, const Vector3 &radiuses, GameObject *parent)
: GameObject(Transform(origin, radiuses), parent), collider(*this, radiuses) {}

SphericObject::SphericObject(const Vector3 &origin, const Vector3 &radiuses, const Vector3 &angles, GameObject *parent)
: GameObject(Transform(origin, radiuses, {0.5,0.5,0.5}, angles), parent), collider(*this, radiuses) {}
        
SphericObject::~SphericObject()
{
}
