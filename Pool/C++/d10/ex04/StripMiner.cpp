/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** StripMiner
*/

#include "StripMiner.hpp"

StripMiner::StripMiner()
{
}

StripMiner::~StripMiner()
{
}

void StripMiner::mine(IAsteroid *a)
{
    if (a == nullptr)
        return;
    std::cout << "* strip mining... got " << a->beMined(this) << "! *" << std::endl;
}