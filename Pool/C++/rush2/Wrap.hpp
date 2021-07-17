/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** Wrap
*/

#pragma once

#include "Object.hpp"

class Wrap : virtual public Object {
    public:
        virtual ~Wrap() {}

        virtual bool wrapMeThat(Object *&) = 0;
        virtual Object *openMe();
        virtual Object *getObject() const;

    protected:
        Object *_object;
    private:
};

Object *MyUnitTests(Object **);
