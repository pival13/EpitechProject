/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** LittlePony
*/

#include "LittlePony.hpp"

LittlePony::LittlePony(const std::string &title)
: Object(title)
{
    _Type = LITTLEPONNY;
}

LittlePony::~LittlePony()
{
}

void LittlePony::isTaken() const
{
    std::cout << "yo man" << std::endl;
}