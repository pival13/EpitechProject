/*
** EPITECH PROJECT, 2020
** cpp_d14a_2019 [WSL: Ubuntu]
** File description:
** RefPtr
*/

#include "RefPtr.hpp"
#include <iostream>

std::list<BaseComponent *> RefPtr::list;

RefPtr::RefPtr(BaseComponent *rawPtr) : _rawPtr(rawPtr)
{
    RefPtr::list.push_back(rawPtr);
}

RefPtr::RefPtr(RefPtr const &other) : _rawPtr(other.get())
{
}

RefPtr::~RefPtr()
{
    RefPtr::list.unique();
    while (!RefPtr::list.empty()) {
        delete RefPtr::list.front();
        RefPtr::list.pop_front();
    }
}

RefPtr &RefPtr::operator=(RefPtr const &other)
{
    _rawPtr = other.get();
    return *this;
}

BaseComponent *RefPtr::get() const { return _rawPtr; }