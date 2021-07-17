/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Priest
*/

#include "Priest.hpp"

Priest::Priest(const std::string &name, int level)
: Character(name, level, "Orc", "Priest", 100, 100, 4, 4, 42, 21, 2)
, Mage(name, level)
{
    std::cout << Name << " enters in the order" << std::endl;
}

Priest::~Priest()
{
}

int Priest::CloseAttack()
{
    if (Power < 10) {
        std::cout << Name << " out of power" << std::endl;
        return 0;
    }
    Power -= 10;
    std::cout << Name << " uses a spirit explosion" << std::endl;
    Range = Character::RANGE;
    return 10 + Spirit;
}

int Priest::RangeAttack() { return Mage::RangeAttack(); }

void Priest::Heal()
{
    if (Power < 10) {
        std::cout << Name << " out of power" << std::endl;
        return;
    }
    Power -= 10;
    std::cout << Name << " casts a little heal spell" << std::endl;
    Pv += 70;
    if (Pv > MaxPv)
        Pv = MaxPv;
}

void Priest::RestorePower() { return Mage::RestorePower(); }