/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** Box
*/

#include "Box.hpp"

Box::Box()
: Object("Box"),_isOpen(false)
{
    _object = nullptr;
    _Type = Object::BOX;
}

Box::~Box()
{
}

bool Box::wrapMeThat(Object *&obj)
{
    if (!_isOpen) {
        std::cerr << "" << std::endl;
        return (false);
    } else if (!obj) {
        std::cerr << "" << std::endl;
        return(false);
    } else if (_object != nullptr) {
        std::cerr << "" << std::endl;
        return(false);
    }
    _object = obj;
    obj = nullptr;
    closeMe();
    return (true);
}

Object *Box::openMe()
{
    if (!_isOpen) {
        _isOpen = true;
        return Wrap::openMe();
    }
    std::cerr << "" << std::endl;
    return(nullptr);
}

void Box::closeMe()
{
    if (_isOpen)
        _isOpen = false;
    else
        std::cerr << "Box is already close" << std::endl;
}
