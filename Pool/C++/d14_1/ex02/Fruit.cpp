/*
** EPITECH PROJECT, 2020
** cpp_d14m_2019 [WSL: Ubuntu]
** File description:
** Fruit
*/

#include "Fruit.hpp"

Fruit::Fruit(const Fruit &f)
: _vitamins(f._vitamins), _name(f.getName())
{
}

std::string Fruit::getName() const { return _name; }
int Fruit::getVitamins() const { return _vitamins; }

Fruit &Fruit::operator=(const Fruit &f)
{
    _name = f.getName();
    _vitamins = f.getVitamins();
    return *this;
}