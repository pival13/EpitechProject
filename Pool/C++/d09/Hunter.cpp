/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Hunter
*/

#include "Hunter.hpp"

Hunter::Hunter(const std::string &name, int level, const std::string weapon)
: Character(name, level, "Elf", "Hunter", 100, 100, 9, 9, 5, 6, 25), Warrior(name, level, weapon)
{
    std::cout << Name << " is born from a tree" << std::endl;
}

Hunter::~Hunter()
{
}

int Hunter::CloseAttack() { return Warrior::CloseAttack(); }

int Hunter::RangeAttack()
{
    if (Power < 25) {
        std::cout << Name << " out of power" << std::endl;
        return 0;
    }
    Power -= 25;
    std::cout << Name << " uses his bow" << std::endl;
    return 20 + Agility;
}

void Hunter::RestorePower()
{
    std::cout << Name << " meditates" << std::endl;
    Power += 100;
    if (Power > MaxPower)
        Power = MaxPower;
}