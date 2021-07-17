/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** CubeCollider
*/

#pragma once

#include "Collider.hpp"

class CubeCollider : public Collider {
    public:
        CubeCollider(GameObject &attachOn);
        CubeCollider(GameObject &attachOn, const Transform &colliderData);
        CubeCollider(GameObject &attachOn, const Vector3 &size, const Vector3 &pos={0,0,0}, const Vector3 &pivot={0.5,0.5,0.5}, const Vector3 &rotate={0,0,0}, const Vector3 &scale={1,1,1});
        ~CubeCollider();

    protected:
        std::vector<Vector3> getCollisionDetectorVector() const;
        std::array<Vector3, 2> getBoundsOnVector(const Vector3 &vectorDirection) const;
};
