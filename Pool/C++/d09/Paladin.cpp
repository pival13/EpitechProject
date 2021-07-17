/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Paladin
*/

#include "Paladin.hpp"

Paladin::Paladin(const std::string &name, int level, const std::string &weapon)
: Character(name, level, "Human", "Paladin", 100, 100, 9, 10, 10, 10, 2)
, Warrior(name, level, weapon), Priest(name, level)
{
    std::cout << "the light falls on " << Name << std::endl;
}

Paladin::~Paladin()
{
}

int Paladin::RangeAttack() { return Mage::RangeAttack(); }

int Paladin::CloseAttack() { return Warrior::CloseAttack(); }

void Paladin::Heal() { return Priest::Heal(); }

void Paladin::RestorePower() { return Character::RestorePower(); }

int Paladin::Intercept() { return Warrior::RangeAttack(); }