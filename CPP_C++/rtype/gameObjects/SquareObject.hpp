/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** SquareObject
*/

#pragma once

#include "CubicObject.hpp"

class SquareObject : public CubicObject {
    public:
        SquareObject(GameObject *parent=nullptr);
        SquareObject(const Vector2 pos, size_t size, GameObject *parent=nullptr);
        SquareObject(const Vector2 pos, const Vector2 sizes, GameObject *parent=nullptr);
        SquareObject(const Vector2 pos, const Vector2 sizes, double angle, GameObject *parent=nullptr);
        ~SquareObject();

    protected:
    private:
};
