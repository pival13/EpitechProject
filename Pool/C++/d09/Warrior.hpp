/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Warrior
*/

#pragma once

#include "Character.hpp"

class Warrior : virtual public Character {
    public:
        Warrior(const std::string &name, int level, const std::string &weaponName="hammer");
        ~Warrior();

        int CloseAttack();
        int RangeAttack();

    protected:
        const std::string Weapon;

    private:
};
