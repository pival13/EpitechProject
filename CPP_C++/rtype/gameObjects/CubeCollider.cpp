/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** CubeCollider
*/

#include "CubeCollider.hpp"

CubeCollider::CubeCollider(GameObject &attachOn)
: Collider(attachOn) {}
CubeCollider::CubeCollider(GameObject &attachOn, const Transform &colliderData)
: Collider(attachOn, colliderData) {}
CubeCollider::CubeCollider(GameObject &attachOn, const Vector3 &size, const Vector3 &pos, const Vector3 &pivot, const Vector3 &rotate, const Vector3 &scale)
: Collider(attachOn, size, pos, pivot, rotate, scale) {}

CubeCollider::~CubeCollider() {}
/*
std::vector<Vector3> CubeCollider::getCollisionDetectorVector() const
{
    auto angles = transform.getGlobalDegRotation();
    return {
        Vector3(1, 0, 0).rotate(Vector3(angles[0], angles[1], angles[2])),
        Vector3(0, 1, 0).rotate(Vector3(angles[0], angles[1], angles[2])),
        Vector3(0, 0, 1).rotate(Vector3(angles[0], angles[1], angles[2]))
    };
}

std::array<Vector3, 2> CubeCollider::getBoundsOnVector(const Vector3 &vectorDirection) const
{
    return {};
}
*/