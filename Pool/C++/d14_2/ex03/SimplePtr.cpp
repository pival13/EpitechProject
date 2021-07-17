/*
** EPITECH PROJECT, 2020
** cpp_d14a_2019 [WSL: Ubuntu]
** File description:
** SimplePtr
*/

#include "SimplePtr.hpp"

SimplePtr::SimplePtr(BaseComponent *rawPtr) : _rawPtr(rawPtr)
{
}

SimplePtr::~SimplePtr()
{
    delete _rawPtr;
}

SimplePtr::SimplePtr(SimplePtr const &) {}
SimplePtr &SimplePtr::operator=(SimplePtr const &) {return *this;}

BaseComponent *SimplePtr::get() const { return _rawPtr; }
