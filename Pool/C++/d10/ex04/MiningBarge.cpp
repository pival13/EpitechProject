/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** MiningBarge
*/

#include "MiningBarge.hpp"

MiningBarge::MiningBarge()
: _laser()
{
}

MiningBarge::~MiningBarge()
{
}

void MiningBarge::equip(IMiningLaser *laser)
{
    for (size_t i = 0; i != _laser.size(); i++)
        if (_laser[i] == laser)
            return;
        else if (_laser[i] == nullptr) {
            _laser[i] = laser;
            return;
        }
}

void MiningBarge::mine(IAsteroid *asteroid) const
{
    if (asteroid == nullptr)
        return;
    for (size_t i = 0; i != _laser.size(); i++)
        if (_laser[i])
            _laser[i]->mine(asteroid);
}