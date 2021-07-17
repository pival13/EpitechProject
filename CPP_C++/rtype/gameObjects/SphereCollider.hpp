/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** SphereCollider
*/

#pragma once

#include "Collider.hpp"

class SphereCollider : public Collider {
    public:
        SphereCollider(GameObject &attachOn);
        SphereCollider(GameObject &attachOn, const Transform &colliderData);
        SphereCollider(GameObject &attachOn, const Vector3 &size, const Vector3 &pos={0,0,0}, const Vector3 &pivot={0.5,0.5,0.5}, const Vector3 &rotate={0,0,0}, const Vector3 &scale={1,1,1});
        ~SphereCollider();

    protected:
        std::vector<Vector3> getCollisionDetectorVector() const { return {}; }
        std::array<Vector3, 2> getBoundsOnVector(const Vector3 &vectorDirection) const;

};
