/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** DeepCoreMiner
*/

#include "DeepCoreMiner.hpp"

DeepCoreMiner::DeepCoreMiner()
{
}

DeepCoreMiner::~DeepCoreMiner()
{
}

void DeepCoreMiner::mine(IAsteroid *a)
{
    if (a == nullptr)
        return;
    std::cout << "* mining deep... got " << a->beMined(this) << "! *" << std::endl;
}