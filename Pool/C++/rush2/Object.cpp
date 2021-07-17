/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** Object
*/

#include "Object.hpp"
#include "LittlePony.hpp"
#include "Teddy.hpp"

Object::Object(const std::string &title)
: _title(title)
{
}

const std::string &Object::getTitle() const { return _title; }

int Object::getType() const {return _Type;}
