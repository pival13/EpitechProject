/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Warrior
*/

#include "Warrior.hpp"

Warrior::Warrior(const std::string &name, int lvl, const std::string &weaponName)
: Character(name, lvl, "Dwarf", "Warrior", 100, 100, 12, 12, 6, 5, 7), Weapon(weaponName)
{
    std::cout << "I'm " << name << " KKKKKKKKKKRRRRRRRRRRRRRREEEEEEEEOOOOOOORRRRGGGGGGG" << std::endl;
}

Warrior::~Warrior()
{
}

int Warrior::CloseAttack()
{
    if (Power < 30) {
        std::cout << Name << " out of power" << std::endl;
        return 0;
    }
    Power -= 30;
    std::cout << Name << " strikes with his " << Weapon << std::endl;
    return 20 + Strength;
}

int Warrior::RangeAttack()
{
    if (Power < 10) {
        std::cout << Name << " out of power" << std::endl;
        return 0;
    }
    Power -= 10;
    std::cout << Name << " intercepts" << std::endl;
    Range = Character::CLOSE;
    return 0;
}