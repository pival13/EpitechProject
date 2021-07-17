/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** SphericObject
*/

#pragma once

#include "GameObject.hpp"
#include "SphereCollider.hpp"

class SphericObject : virtual public GameObject {
    public:
        SphericObject(GameObject *parent=nullptr);
        SphericObject(const Vector3 &origin, size_t radius, GameObject *parent=nullptr);
        SphericObject(const Vector3 &origin, const Vector3 &radiuses, GameObject *parent=nullptr);
        SphericObject(const Vector3 &origin, const Vector3 &radiuses, const Vector3 &angles, GameObject *parent=nullptr);
        ~SphericObject();

    protected:
        SphereCollider collider;
};
