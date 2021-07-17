/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Hunter
*/

#pragma once

#include "Warrior.hpp"

class Hunter : private Warrior, virtual public Character {
    public:
        Hunter(const std::string &name, int level, const std::string weapon="sword");
        ~Hunter();

        int CloseAttack();
        int RangeAttack();
        void RestorePower();

    protected:

    private:
};
