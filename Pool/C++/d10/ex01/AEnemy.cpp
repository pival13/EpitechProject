/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** AEnemy
*/

#include "AEnemy.hpp"

AEnemy::AEnemy(int hp, const std::string &type)
: _type(type), _hp(hp)
{
}

AEnemy::~AEnemy()
{
}

const std::string AEnemy::getType() const { return _type; }
int AEnemy::getHP() const { return _hp; }

void AEnemy::takeDamage(int damage)
{
    if (damage < 0)
        return;
    _hp -= damage;
}