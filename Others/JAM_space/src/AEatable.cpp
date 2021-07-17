/*
** EPITECH PROJECT, 2020
** AEatable.cpp
** File description:
** aeatable
*/

#include "AEatable.hpp"

using namespace Jam;

AEatable::AEatable()
{
}

void AEatable::edibleCheck(sf::RenderWindow & window, sf::Event & event)
{
    compute(event);
    draw(window);
}

size_t& AEatable::getNutritiveValue()
{
    return _nutritiveValue;
}

sf::Vector2f AEatable::getSpeed()
{
    return {0, 0};
}