/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** CubicObject
*/

#pragma once

#include "GameObject.hpp"
#include "CubeCollider.hpp"

class CubicObject : virtual public GameObject {
    public:
        CubicObject(GameObject *parent=nullptr);
        CubicObject(const Vector3 &origin, size_t size, GameObject *parent=nullptr);
        CubicObject(const Vector3 &origin, const Vector3 &sizes, GameObject *parent=nullptr);
        CubicObject(const Vector3 &origin, const Vector3 &sizes, const Vector3 &angle, GameObject *parent=nullptr);
        ~CubicObject();

    protected:
        CubeCollider collider;
};
