/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** Wrap
*/

#include "Wrap.hpp"
#include "Toy.hpp"
#include "Box.hpp"
#include "GiftPaper.hpp"

Object *Wrap::openMe()
{
    Object *obj = _object;
    _object = nullptr;
    return obj;
}

Object *Wrap::getObject() const 
{ 
    if (_object == nullptr)
        return (nullptr);
    return (_object);
}