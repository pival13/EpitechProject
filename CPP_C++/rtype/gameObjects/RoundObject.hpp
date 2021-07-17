/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RoundObject
*/

#pragma once

#include "SphericObject.hpp"

class RoundObject : public SphericObject {
    public:
        RoundObject(GameObject *parent=nullptr);
        RoundObject(const Vector2 &pos, size_t radius, GameObject *parent=nullptr);
        RoundObject(const Vector2 &pos, const Vector2 radiuses, GameObject *parent=nullptr);
        RoundObject(const Vector2 &pos, const Vector2 radiuses, double angle, GameObject *parent=nullptr);
        ~RoundObject();

    protected:
    private:
};
