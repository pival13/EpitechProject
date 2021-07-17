/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** Teddy
*/

#include "Teddy.hpp"

Teddy::Teddy(const std::string &title)
: Object(title)
{
    _Type = TEDDY;
}

Teddy::~Teddy()
{
}

void Teddy::isTaken() const
{
    std::cout << "gra hu" << std::endl;
}