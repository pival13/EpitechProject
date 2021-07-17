/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** CannonFodder
*/

#include "CannonFodder.hpp"

CannonFodder::CannonFodder(const std::string &teamName)
: Trantorian(teamName)
{
}

CannonFodder::~CannonFodder()
{
}

void CannonFodder::launch()
{
    while (_isAlive)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void CannonFodder::remainingPlace(size_t)
{
    for (size_t i = 0; i != 9; i++)
        drop("food");
}
