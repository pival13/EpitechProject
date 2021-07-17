/*
** EPITECH PROJECT, 2020
** cpp_d14m_2019 [WSL: Ubuntu]
** File description:
** Mixer
*/

#include "Mixer.hpp"

Mixer::Mixer()
{
    _plugged = false;
    _mixfunc = [](FruitBox &b) {
        int vit = 0;
        while (b.nbFruits() > 0)
            vit += b.pickFruit()->getVitamins();
        return vit;
    };
}

Mixer::~Mixer()
{
}

int Mixer::mix(FruitBox &fruits) const
{
    if (_plugged)
        return _mixfunc(fruits);
    else
        return 0;
}

void Mixer::plug()
{
    _plugged = !_plugged;
}
