/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** SphereCollider
*/

#include "SphereCollider.hpp"

SphereCollider::SphereCollider(GameObject &attachOn)
: Collider(attachOn) {}
SphereCollider::SphereCollider(GameObject &attachOn, const Transform &colliderData)
: Collider(attachOn, colliderData) {}
SphereCollider::SphereCollider(GameObject &attachOn, const Vector3 &size, const Vector3 &pos, const Vector3 &pivot, const Vector3 &rotate, const Vector3 &scale)
: Collider(attachOn, size, pos, pivot, rotate, scale) {}

SphereCollider::~SphereCollider()
{
}
/*
std::array<Vector3, 2> SphereCollider::getBoundsOnVector(const Vector3 &vectorDirection) const
{
    return {};
}
*/