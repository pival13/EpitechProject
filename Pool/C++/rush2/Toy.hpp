/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** Toy
*/

#pragma once

#include "Object.hpp"

class Toy : virtual public Object {
    public:
        virtual ~Toy() {}

        virtual void isTaken() const = 0;

    protected:
    private:
};
