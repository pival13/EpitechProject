/*
** EPITECH PROJECT, 2020
** IconveyorBelt.hpp
** File description:
** IconveyorBelt.hpp
*/
#pragma once
#include "Wrap.hpp"

class IConveyorBelt {
public:
    virtual void InButton() = 0;
    virtual void OutButton() = 0;
    virtual bool isEmpty() const = 0;
    virtual Object *&getObject() = 0;
    virtual void addObject(Object *&obj) = 0;

protected:
    Object *_conv_obj;
private:
};
