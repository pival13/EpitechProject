/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Mage
*/

#pragma once

#include "Character.hpp"

class Mage : virtual public Character {
    public:
        Mage(const std::string &name, int level);
        ~Mage();

        int CloseAttack();
        int RangeAttack();
        void RestorePower();

    protected:

    private:
};
