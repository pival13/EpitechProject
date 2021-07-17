/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Collider
*/

#pragma once

#include "GameObject.hpp"

class Collider {
    public:
        virtual ~Collider();

        Transform getTransform() const { return transform; }
        Transform &getTransform() { return transform; }

        void checkBoundary(const std::list<Collider *> &colliders);

        bool operator==(const Collider &);

    protected:
        Collider(GameObject &attachOn);
        Collider(GameObject &attachOn, const Transform &colliderData);
        Collider(GameObject &attachOn, const Vector3 &size, const Vector3 &pos, const Vector3 &pivot, const Vector3 &rotate, const Vector3 &scale);
        //virtual std::vector<Vector3> getCollisionDetectorVector() const = 0;//Normals of each side of the collider
        //virtual std::array<Vector3, 2> getBoundsOnVector(const Vector3 &vectorDirection) const = 0;//Extrema's coordinates of the projection of the collider on the vector

    public:
        std::function<void(Collider &other)> onCollision;
        GameObject &gameObject;

    protected:
        Transform transform;
};
