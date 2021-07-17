/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Mage
*/

#include "Mage.hpp"

Mage::Mage(const std::string &name, int level)
: Character(name, level, "Gnome", "Mage", 100, 100, 6, 6, 12, 11, 7)
{
    std::cout << Name << " teleported" << std::endl;
}

Mage::~Mage()
{
}

int Mage::CloseAttack()
{
    if (Power < 10) {
        std::cout << Name << " out of power" << std::endl;
        return 0;
    }
    Power -= 10;
    std::cout << Name << " blinks" << std::endl;
    Range = Character::RANGE;
    return 0;
}

int Mage::RangeAttack()
{
    if (Power < 25) {
        std::cout << Name << " out of power" << std::endl;
        return 0;
    }
    Power -= 25;
    std::cout << Name << " launches a fire ball" << std::endl;
    return 20 + Spirit;
}

void Mage::RestorePower()
{
    std::cout << Name << " takes a mana potion" << std::endl;
    Power += 50 + Intelligence;
    if (Power > MaxPower)
        Power = MaxPower;
}